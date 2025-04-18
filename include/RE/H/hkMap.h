#pragma once

#include "RE/H/hkContainerAllocators.h"
#include "RE/H/hkMemoryRouter.h"

namespace RE
{
	/// Default operations for hkMaps
	template <typename KEY>
	struct hkMapOperations
	{
		inline static uint32_t hash(KEY key, uint32_t mod)
		{
			// We ignore the lowest four bits on the address, since most addresses will be 16-byte aligned
			// knuths multiplicative golden hash
			return uint32_t((uint32_t(key) >> 4) * 2654435761U) & mod;
		}
		inline static void invalidate(KEY& key)
		{
			key = KEY(-1);
		}
		inline static bool isValid(KEY key)
		{
			return key != KEY(-1);
		}
		inline static bool equal(KEY key0, KEY key1)
		{
			return key0 == key1;
		}
	};

	// Specialized version without shifting away the bottom bits
	template <>
	struct hkMapOperations<int>
	{
		inline static uint32_t hash(int key, uint32_t mod) { return (uint32_t(key) * 2654435761U) & mod; }
		inline static void     invalidate(int& key) { key = int(-1); }
		inline static bool     isValid(int key) { return key != int(-1); }
		inline static bool     equal(int key0, int key1) { return key0 == key1; }
	};

	/// A class to store key, value pairs.
	/// Note that the key must have an invalid or reserved state which is used to mark
	/// empty slots. For instance by default -1 is disallowed as a integer key. You can override
	/// this behavior by instantiating with a custom operations structure.
	template <typename KEY, typename VAL = KEY, typename OPS = hkMapOperations<KEY>>
	class hkMapBase
	{
	public:
		using size_type = int32_t;

		HK_HEAP_REDEFINE_NEW_NOVIRTUAL(hkMapBase);

		struct Pair
		{
			// members
			KEY key;  // 00
			VAL val;  // ??
		};

		// Internal flags, set in constructor.
		enum : uint32_t
		{
			NUM_ELEMS_MASK = uint32_t(0x7FFFFFFF),
			DONT_DEALLOCATE_FLAG = uint32_t(0x80000000)  // Indicates that the storage is not the map's to delete
		};

		/// Iterator type.
		/// All iterators are invalidated after a mutating operation, i.e., insertion, removal.
		typedef class Dummy* Iterator;
#define HK_MAP_INDEX_TO_ITERATOR(i) reinterpret_cast<Iterator>(hkUlong(i))
#define HK_MAP_ITERATOR_TO_INDEX(it) static_cast<int>(reinterpret_cast<hkUlong>(it))

		/// Create an empty pointer map.
		hkMapBase() :
			m_elem(nullptr), m_numElems(0), m_hashMod(-1) {}

		/// Create pointer map initially using preallocated memory block.
		/// Use the getSizeInBytesFor(int numKeys) method to find the buffer size
		/// required for a given number of keys.
		hkMapBase(void* ptr, size_type sizeInBytes)
		{
			init(ptr, sizeInBytes);
		}

		~hkMapBase()
		{
			assert(!shouldDeallocate() || m_elem == nullptr);  // memory not freed
		}


		bool shouldDeallocate() const
		{
			return (m_numElems & DONT_DEALLOCATE_FLAG) == 0;
		}

		/// Return the number of keys.
		size_type getSize() const
		{
			return m_numElems & NUM_ELEMS_MASK;
		}

		void reserve(hkMemoryAllocator& allocator, size_type numElements)
		{
			// Make sure that the actual table size is not going to be less than twice the current number of elements
			assert(numElements >= 0 && getSize() * 2 <= numElements * 3);
			size_type minCap = numElements * 2;
			size_type cap = s_minimumCapacity;
			while (cap < minCap) {
				cap *= 2;
			}

			resizeTable(allocator, cap);
		}

		/// Insert key with associated value val. Keys are unique and by default
		/// (if using hkPointerMapOperations) cannot be -1.
		/// If key already exists it is overwritten.
		bool insert(hkMemoryAllocator& alloc, KEY key, VAL val)
		{
			assert(OPS::isValid(key));  // "pointer map keys must not be the empty value"

			// This is quite conservative. We could grow more
			// slowly at the cost of potentially longer searches.
			{
				size_type numElems = getSize();
				if (numElems + numElems > m_hashMod) {
					resizeTable(alloc, m_hashMod + m_hashMod + 2);
				}
			}

			uint32_t i;
			bool     isNewKey = true;
			for (i = OPS::hash(key, m_hashMod); OPS::isValid(m_elem[i].key); i = (i + 1) & m_hashMod) {
				// find free slot
				if (OPS::equal(m_elem[i].key, key)) {
					isNewKey = false;
					break;
				}
			}

			// dont increment m_numElems if overwriting.
			m_numElems += isNewKey;

			// insert key,value
			m_elem[i].key = key;
			m_elem[i].val = val;
			return isNewKey;
		}

		/// Return the value associated with key or def if not present.
		VAL getWithDefault(KEY key, VAL def) const
		{
			if (m_hashMod > 0) {
				for (uint32_t i = OPS::hash(key, m_hashMod); OPS::isValid(m_elem[i].key); i = (i + 1) & m_hashMod) {
					if (OPS::equal(m_elem[i].key, key)) {
						return m_elem[i].val;
					}
				}
			}
			return def;
		}

		void clear()
		{
			size_type capacity = m_hashMod + 1;
			for (size_type i = 0; i < capacity; i++) {
				OPS::invalidate(m_elem[i].key);
			}
			m_numElems = 0 | (m_numElems & static_cast<int32_t>(DONT_DEALLOCATE_FLAG));
		}

		void clearAndDeallocate(hkMemoryAllocator& allocator)
		{
			clear();
			if (shouldDeallocate()) {
				allocator.BlockFree(m_elem, static_cast<int32_t>(sizeof(Pair) * (m_hashMod + 1)));
			}
			m_elem = nullptr;
			m_numElems = 0;
			m_hashMod = -1;
		}

		// members
		Pair* m_elem;		   // 00
		size_type m_numElems;  // 08 - high bits are flags
		size_type m_hashMod;   // 0C - capacity - 1

	protected:
		static const int s_minimumCapacity = 8;

		static inline bool isPower2(uint32_t v) { return (v & (v - 1)) == 0; }

		void init(void* ptr, size_type sizeInBytes)
		{
			size_type maxKeys = uint32_t(sizeInBytes) / (sizeof(Pair));

			assert(maxKeys >= s_minimumCapacity);
			assert(isPower2(maxKeys));
			assert(maxKeys * sizeof(Pair) == sizeInBytes);

			m_elem = static_cast<Pair*>(ptr);
			m_numElems = DONT_DEALLOCATE_FLAG;
			m_hashMod = maxKeys - 1;

			for (size_type i = 0; i < maxKeys; i++) {
				OPS::invalidate(m_elem[i].key);
			}
		}

		void resizeTable(hkMemoryAllocator& alloc, size_type newcap)
		{
			newcap = std::max(newcap, s_minimumCapacity);

			assert(m_numElems < newcap);  // "table size is not big enough"

			bool     _shouldDeallocate = shouldDeallocate();
			size_type oldcap = m_hashMod + 1;
			Pair*    oldelem = m_elem;
			Pair*    newelem = static_cast<Pair*>(alloc.BlockAlloc(sizeof(Pair) * newcap));

			assert(newelem != nullptr);

			m_elem = newelem;

			for (size_type i = 0; i < newcap; i++) {
				OPS::invalidate(m_elem[i].key);
			}
			m_numElems = 0;
			m_hashMod = newcap - 1;

			for (size_type i = 0; i < oldcap; ++i) {
				if (OPS::isValid(oldelem[i].key)) {
					insert(alloc, oldelem[i].key, oldelem[i].val);
				}
			}

			if (!_shouldDeallocate) {
				alloc.BlockFree(oldelem, sizeof(Pair) * oldcap);
			}
		}
	};

	template <typename KEY, typename VAL = KEY, typename OPS = hkMapOperations<KEY>, typename Allocator = hkContainerHeapAllocator>
	class hkMap : public hkMapBase<KEY, VAL, OPS>
	{
	public:
		using size_type = hkMapBase<KEY, VAL, OPS>::size_type;
		using operations = OPS;

		explicit hkMap(size_type nelem = 0)
		{
			if (nelem) {
				reserve(nelem);
			}
		}

		/// Create pointer map initially using preallocated memory block.
		/// Use the getSizeInBytesFor(int numKeys) method to find the buffer size
		/// required for a given number of keys.
		hkMap(void* ptr, size_type sizeInBytes) :
			hkMapBase<KEY, VAL, OPS>(ptr, sizeInBytes) {}

		/// Destroy a pointer map.
		~hkMap() { hkMapBase<KEY, VAL, OPS>::clearAndDeallocate(*Allocator::GetSingleton()); }

		/// Insert key with associated value val. Keys are unique and by default
		/// (if using hkPointerMapOperations) cannot be -1.
		/// If key already exists it is overwritten.
		bool insert(KEY key, VAL val) { return hkMapBase<KEY, VAL, OPS>::insert(*Allocator::GetSingleton(), key, val); }

		// Estimates and sets the appropriate table size for a given number of elements.
		void reserve(size_type numElements) { return hkMapBase<KEY, VAL, OPS>::reserve(*Allocator::GetSingleton(), numElements); }
	};

	// Helpers to get the hkMap implementation for a given key size.
	template <int32_t N>
	struct hkPointerMapStorage
	{
		typedef int64_t Type;  // idk why hkbStateMachine::StateIdToIndexMap uses int64_t
	};
	template <>
	struct hkPointerMapStorage<8>
	{
		typedef uint64_t Type;
	};

	/// A class to map between pointer or integer keys and arbitrary pointer/integer values.
	/// The key is not allowed to be -1.
	template <typename K, typename V, typename Allocator = hkContainerHeapAllocator>
	class hkPointerMap
	{
	public:
		using size_type = int32_t;

		HK_HEAP_REDEFINE_NEW_NOVIRTUAL(hkPointerMap);

		using Storage = hkPointerMapStorage<sizeof(K)>::Type;
		using ValueCast = hkPointerMapStorage<sizeof(V)>::Type;

		/// Create an empty pointermap.
		hkPointerMap()
		{
		}

		/// Create pointer map initially using preallocated memory block.
		/// Use the getSizeInBytesFor(int numKeys) method to find the buffer size
		/// required for a given number of keys.
		hkPointerMap(void* ptr, size_type sizeInBytes) :
			m_map(ptr, sizeInBytes)
		{
		}

		~hkPointerMap() = default;

		/// Insert key with associated value val. Keys are unique and by default
		/// (if using hkPointerMapOperations) cannot be -1.
		/// If key already exists it is overwritten.
		bool insert(K key, V val)
		{
			return m_map.insert(Storage(key), ValueCast(val));
		}

		// Estimates and sets the appropriate table size for a given number of elements.
		void reserve(size_type numElements)
		{
			return m_map.reserve(numElements);
		}

		void clear()
		{
			return m_map.clear();
		}

		/// Return the value associated with key or def if not present.
		V getWithDefault(K key, V def) const
		{
			return (V)(ValueCast)m_map.getWithDefault(Storage(key), ValueCast(def));
		}

		/// Return the number of elements in this map.
		size_type getSize() const
		{
			return m_map.getSize();
		}

		/// Return the number of elements that can be stored in this map without reallocation.
		size_type getCapacity() const
		{
			return m_map.getCapacity();
		}

		// members
		hkMap<Storage, Storage, hkMapOperations<Storage>, Allocator> m_map;  // 00
	};

	//struct hkMap64
	//{
	//public:
	//	uint32_t insert(int64_t key, int64_t val)
	//	{
	//		REL::Relocation<uint32_t(hkMap64*, void*, uint64_t key, int64_t val)> func(RELOCATION_ID(56771, 0));
	//		return func(this, RE::hkContainerHeapAllocator::GetSingleton(), key, val);
	//	}
	//
	//	int64_t getWithDefault(int64_t key, int64_t val_default)
	//	{
	//		REL::Relocation<int64_t(hkMap64*, int64_t, int64_t)> func(RELOCATION_ID(56768, 0));
	//		return func(this, key, val_default);
	//	}
	//
	//private:
	//	struct Entry
	//	{
	//		uint64_t key;
	//		uint64_t val;
	//	};
	//	static_assert(sizeof(Entry) == 0x10);
	//
	//public:
	//	// members
	//	Entry*   data;
	//	uint32_t size;
	//	uint32_t cap;
	//};
	//static_assert(sizeof(hkMap64) == 0x10);
}
