#pragma once

#include "RE/H/hkContainerAllocators.h"

namespace RE
{
	namespace hkArrayUtil
	{
		void _reserve(hkMemoryAllocator& allocator, void* _array, int32_t reqElem, int32_t sizeElem);
		void _reserveMore(hkMemoryAllocator& allocator, void* _array, int32_t sizeElem);
		void _reduce(hkMemoryAllocator& allocator, void* _array, int32_t sizeElem, void* inplaceMem, int32_t requestedCapacity);

		template <typename T>
		void construct(T* t, int32_t n)
		{
			for (int32_t i = 0; i < n; ++i) {
				::new (t + i) T();
			}
		}

		template <typename T>
		void constructWithCopy(T* t, int32_t n, const T& tcopy)
		{
			for (int32_t i = 0; i < n; ++i) {
				::new (t + i) T(tcopy);
			}
		}

		template <typename T>
		void destruct(T* t, int32_t n)
		{
			for (int32_t i = n - 1; i >= 0; --i) {
				t[i].~T();
			}
		}

		template <typename T>
		void constructWithArray(T* t, int32_t n, const T* tcopy)
		{
			for (int32_t i = 0; i < n; ++i) {
				::new (t + i) T(tcopy[i]);
			}
		}
	}

	template <class T>
	class hkArrayBase
	{
	public:
		using value_type = T;
		using size_type = std::int32_t;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = T*;
		using const_iterator = const T*;

		hkArrayBase() = default;
		~hkArrayBase()
		{
			assert(!shouldDeallocate());  // Array memory not freed
		}

		/// Noncopying initialization from an existing external buffer.
		/// This does not copy the array but uses it in place until its capacity
		/// is exceeded at which point a reallocation occurs and the array behaves
		/// like a normal hkArray.
		/// The caller must ensure that the buffer is valid for the lifetime
		/// of this array and for deallocation of the buffer.
		hkArrayBase(T* buffer, int size, int capacity) :
			_data(buffer), _size(size), _capacityAndFlags(capacity | kDontDeallocFlag)
		{
			assert(size >= 0);
			assert(capacity >= 0);
			assert(size <= capacity);
		}

	protected:
		/// Array cannot be copied without explicit allocator.
		hkArrayBase(const hkArrayBase& a) { assert(false); }

		/// Array cannot be copied without explicit allocator.
		hkArrayBase& operator=(const hkArrayBase& a)
		{
			assert(false);
			return *this;
		}

	public:
		bool shouldDeallocate() const
		{
			return (_capacityAndFlags & kDontDeallocFlag) == 0;
		}

		reference operator[](size_type a_pos)
		{
			assert(a_pos >= 0 && a_pos < size());
			return data()[a_pos];
		}

		const_reference operator[](size_type a_pos) const
		{
			assert(a_pos >= 0 && a_pos < size());
			return data()[a_pos];
		}

		T* data()
		{
			return _data;
		}

		[[nodiscard]] const T* data() const
		{
			return _data;
		}

		void _setDataUnchecked(T* ptr, size_type size, size_type capacityAndFlags)
		{
			_data = ptr;
			_size = size;
			_capacityAndFlags = capacityAndFlags;
		}

		reference front()
		{
			assert(!empty());
			return operator[](0);
		}

		[[nodiscard]] const_reference front() const
		{
			assert(!empty());
			return operator[](0);
		}

		reference back()
		{
			assert(!empty());
			return operator[](size() - 1);
		}

		[[nodiscard]] const_reference back() const
		{
			assert(!empty());
			return operator[](size() - 1);
		}

		iterator begin()
		{
			return empty() ? iterator{} : std::addressof(data()[0]);
		}

		[[nodiscard]] const_iterator begin() const
		{
			return empty() ? const_iterator{} : std::addressof(data()[0]);
		}

		[[nodiscard]] const_iterator cbegin() const
		{
			return begin();
		}

		iterator end()
		{
			return empty() ? iterator{} : std::addressof(data()[size()]);
		}

		[[nodiscard]] const_iterator end() const
		{
			return empty() ? const_iterator{} : std::addressof(data()[size()]);
		}

		[[nodiscard]] const_iterator cend() const
		{
			return end();
		}

		[[nodiscard]] bool empty() const
		{
			return size() == 0;
		}

		[[nodiscard]] size_type size() const noexcept
		{
			return _size;
		}

		[[nodiscard]] size_type capacity() const noexcept
		{
			return _capacityAndFlags & kCapacityMask;
		}

		void _reserve(hkMemoryAllocator& allocator, size_type n)
		{
			assert(n <= kCapacityMask);

			size_type cap = capacity();
			if (cap < n) {
				size_type cap2 = 2 * cap;
				size_type newSize = std::max(n, cap2);
				hkArrayUtil::_reserve(allocator, this, newSize, sizeof(T));
			}
		}

		void _pushBack(hkMemoryAllocator& allocator, const T& t)
		{
			if (size() == capacity()) {
				assert(!((&t >= data()) && (&t < (data() + size()))));  // "hkArrayBase::pushBack can't push back element of same array during resize"
				hkArrayUtil::_reserveMore(allocator, this, sizeof(T));
			}
			hkArrayUtil::constructWithCopy<T>(data() + size(), 1, t);
			_size++;
		}

		void _append(hkMemoryAllocator& alloc, const T* a, size_type numtoinsert)
		{
			size_type newsize = size() + numtoinsert;
			if (newsize > capacity()) {
				_reserve(alloc, newsize);
			}
			hkArrayUtil::constructWithArray(data() + size(), numtoinsert, a);
			_size = newsize;
		}

		void copy(T* dst, const T* src, size_type n)
		{
			assert(dst <= src || src + n <= dst);
			for (size_type i = 0; i < n; ++i) {
				dst[i] = src[i];
			}
		}

		hkArrayBase& copyFromArray(hkMemoryAllocator& allocator, const hkArrayBase& a)
		{
			size_type oldSize = size();
			size_type newSize = a.size();
			size_type copiedSize = newSize > oldSize ? oldSize : newSize;

			_reserve(allocator, newSize);                                                                       // ensure space
			hkArrayUtil::destruct(data() + newSize, oldSize - newSize);                                         // destruct items past the size of a, if any
			copy(data(), a.data(), copiedSize);                                                                 // copy objects into the 'live' part of this array
			hkArrayUtil::constructWithArray(data() + copiedSize, newSize - copiedSize, a.data() + copiedSize);  // and construct the rest
			_size = newSize;
			return *this;
		}

		void _setSize(hkMemoryAllocator& allocator, size_type n)
		{
			_reserve(allocator, n);
			hkArrayUtil::destruct(data() + n, size() - n);
			hkArrayUtil::construct(data() + size(), n - size());
			_size = n;
		}

		void _setSize(hkMemoryAllocator& allocator, size_type n, const T& fill)
		{
			_reserve(allocator, n);
			hkArrayUtil::destruct(data() + n, size() - n);
			hkArrayUtil::constructWithCopy(data() + size(), n - size(), fill);
			_size = n;
		}

		void clear()
		{
			hkArrayUtil::destruct(data(), size());
			_size = 0;
		}

		void _clearAndDeallocate(hkMemoryAllocator& allocator)
		{
			clear();
			if (shouldDeallocate()) {
				allocator.BufFree(data(), capacity() * sizeof(T));
			}
			_data = nullptr;
			_capacityAndFlags = kDontDeallocFlag;
		}

		enum : std::uint32_t
		{
			kCapacityMask = 0x3FFFFFFF,
			kFlagMask = 0xC0000000,
			kDontDeallocFlag = (std::uint32_t)1 << 31
		};

		T*            _data{ nullptr };                       // 00
		std::int32_t  _size{ 0 };                             // 08
		std::uint32_t _capacityAndFlags{ kDontDeallocFlag };  // 0C
	};
	static_assert(sizeof(hkArrayBase<void*>) == 0x10);

	template <class T, class Allocator = hkContainerHeapAllocator>
	class hkArray : public hkArrayBase<T>
	{
	public:
		using ThisType = hkArrayBase<T>;
		using size_type = ThisType::size_type;

		/// Creates a zero length array.
		hkArray() :
			ThisType() {}

		~hkArray()
		{
			clearAndDeallocate();
		}

		/// Creates an array of size n. All elements are uninitialized.
		explicit hkArray(size_type n) :
			ThisType()
		{
			hkMemoryAllocator& allocator = Allocator::GetSingleton();
			const size_type    size = n;
			T*                 p = n ? allocator._bufAlloc<T>(n) : nullptr;
			size_type          cap = n ? n : hkArrayBase<T>::kDontDeallocFlag;
			hkArrayBase<T>::_setDataUnchecked(p, size, cap);
			hkArrayUtil::construct(p, size);
		}

		/// Creates an array of n elements initialized to 'fill'.
		hkArray(size_type n, const T& fill) :
			ThisType()
		{
			hkMemoryAllocator& allocator = Allocator::GetSingleton();
			const size_type    size = n;
			T*                 p = n ? allocator._bufAlloc<T>(n) : nullptr;
			size_type          cap = n ? n : hkArrayBase<T>::kDontDeallocFlag;
			hkArrayBase<T>::_setDataUnchecked(p, size, cap);
			hkArrayUtil::constructWithCopy(p, size, fill);
		}

		/// Noncopying initialization from an existing external buffer.
		/// This does not copy the array but uses it in place until its capacity
		/// is exceeded at which point a reallocation occurs and the array behaves
		/// like a normal hkArray.
		/// The caller must ensure that the buffer is valid for the lifetime
		/// of this array and for deallocation of the buffer.
		hkArray(T* buffer, int size, int capacity) :
			ThisType(buffer, size, capacity) {}

		/// Copy another array
		hkArray& operator=(const hkArrayBase<T>& a)
		{
			hkArrayBase<T>::copyFromArray(*Allocator::GetSingleton(), a);
			return *this;
		}

		hkArray& operator=(const hkArray& a)
		{
			hkArrayBase<T>::copyFromArray(*Allocator::GetSingleton(), a);
			return *this;
		}

		void reserve(size_type size)
		{
			hkArrayBase<T>::_reserve(*Allocator::GetSingleton(), size);
		}

		void resize(size_type size)
		{
			hkArrayBase<T>::_setSize(*Allocator::GetSingleton(), size);
		}

		void resize(size_type size, const T& fill)
		{
			hkArrayBase<T>::_setSize(*Allocator::GetSingleton(), size, fill);
		}

		void push_back(const T& e)
		{
			hkArrayBase<T>::_pushBack(*Allocator::GetSingleton(), e);
		}

		void append(const T* a, size_type numElems)
		{
			hkArrayBase<T>::_append(*Allocator::GetSingleton(), a, numElems);
		}

		template <typename K>
		void append(const hkArrayBase<K>& other)
		{
			append(other.begin(), other.size());
		}

		void clearAndDeallocate()
		{
			hkArrayBase<T>::_clearAndDeallocate(*Allocator::GetSingleton());
		}

		/// [Not] publicly accessible, too easy to call accidentally.
		hkArray(const hkArray& arr) :
			hkArrayBase<T>()
		{
			size_type          n = arr.size();
			size_type          this_size = n;
			hkMemoryAllocator& a = *Allocator::GetSingleton();
			T*                 p = n ? a._bufAlloc<T>(n) : nullptr;
			size_type          cap = n ? n : hkArrayBase<T>::kDontDeallocFlag;
			hkArrayBase<T>::_setDataUnchecked(p, this_size, cap);
			hkArrayUtil::constructWithArray(p, this_size, arr.data());
		}
	};
	static_assert(sizeof(hkArray<void*>) == 0x10);

	template <class T, std::size_t N, class Allocator = hkContainerHeapAllocator>
	class hkInplaceArray : public hkArray<T, Allocator>
	{
	public:
		hkInplaceArray() :
			hkArray<T, Allocator>()
		{
			this->_capacityAndFlags |= hkArray<T, Allocator>::kDontDeallocFlag;
			this->_data = &storage[0];
		}

		T storage[N];  // 10
	};
}
