#pragma once

#include "RE/M/MemoryManager.h"

namespace RE
{
	class ScrapHeap;

	class BSTArrayBase
	{
	public:
		using size_type = uint32_t;

		constexpr BSTArrayBase() noexcept = default;
		constexpr BSTArrayBase(const BSTArrayBase&) noexcept = default;
		constexpr BSTArrayBase(BSTArrayBase&& other) :
			_size(other._size) { other._size = 0; }

		~BSTArrayBase() noexcept { _size = 0; }

		BSTArrayBase& operator=(const BSTArrayBase&) = delete;
		BSTArrayBase& operator=(BSTArrayBase&& other) = delete;

		[[nodiscard]] constexpr bool      empty() const noexcept { return _size == 0; }
		[[nodiscard]] constexpr size_type size() const noexcept { return _size; }

	protected:
		static void swap(BSTArrayBase& left, BSTArrayBase& right) noexcept { std::swap(left._size, right._size); }
		void        set_size(size_type new_size) { _size = new_size; }

	private:
		// members
		uint32_t _size{ 0 };  // 0
	};
	static_assert(sizeof(BSTArrayBase) == 0x4);

	class BSTArrayHeapAllocator
	{
		// invariant: data == nullptr <=> cap == 0
		using size_type = typename BSTArrayBase::size_type;
		using traits_info = std::pair<void*, size_type>;

	protected:
		constexpr BSTArrayHeapAllocator() noexcept = default;
		BSTArrayHeapAllocator(const BSTArrayHeapAllocator& other) = delete;
		BSTArrayHeapAllocator(BSTArrayHeapAllocator&& other) = delete;
		~BSTArrayHeapAllocator() = default;  // BSTArray deallocated & destroyed
		BSTArrayHeapAllocator& operator=(const BSTArrayHeapAllocator& other) = delete;
		BSTArrayHeapAllocator& operator=(BSTArrayHeapAllocator&& other) = delete;

		[[nodiscard]] constexpr void*       data() noexcept { return _data; }
		[[nodiscard]] constexpr const void* data() const noexcept { return _data; }
		[[nodiscard]] constexpr size_type   capacity() const noexcept { return _capacity; }

	protected:
		[[nodiscard]] traits_info Allocate(size_type count, size_type elem_size)
		{
			assert(count > 0 && "Allocate with 0 count");
			return { allocate_and_check(count * elem_size), count };
		}

		void* AllocateAndRemember(size_type count, size_type elem_size) { return set_traits(Allocate(count, elem_size)); }

		// must be returned by Allocate
		void SetTraits(traits_info info) { set_traits(std::move(info)); }

		void Deallocate(void* ptr) { free(ptr); }

		void Deallocate()
		{
			free(_data);
			set_traits({ nullptr, 0 });
		}

		static void swap(BSTArrayHeapAllocator& left, const BSTArrayBase&, BSTArrayHeapAllocator& right, const BSTArrayBase&)
		{
			std::swap(left._data, right._data);
			std::swap(left._capacity, right._capacity);
		}

	private:
		// then assume it is not nullptr
		void* allocate_and_check(size_type bytes)
		{
			auto mem = malloc(bytes);
			if (!mem) {
				assert(false && "OOM");
				stl::report_and_fail("out of memory"sv);
			}
			return mem;
		}

		constexpr void* set_traits(traits_info info) noexcept
		{
			_data = info.first;
			_capacity = info.second;
			return _data;
		}

		// members
		void*    _data{ nullptr };        // 00
		uint32_t _capacity{ 0 };          // 08 - number of elements (not bytes)
		uint32_t pad0C [[maybe_unused]];  // 0C
	};
	static_assert(sizeof(BSTArrayHeapAllocator) == 0x10);

	template <typename T, uint32_t StaticSizeInBytes>
	class BSTSmallArrayHeapAllocator
	{
		// invariant:
		//   _local == 1:
		//     active union field is local
		//     _capacity == static_capacity
		//   _local == 0:
		//     active union field is heap
		//     capacity() == _capacity
		using size_type = typename BSTArrayBase::size_type;
		using traits_info = std::pair<void*, size_type>;
		using value_type = T;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		static constexpr size_type elem_size = sizeof(value_type);

		static constexpr size_type static_capacity = StaticSizeInBytes / elem_size;
		static_assert(StaticSizeInBytes % elem_size == 0, "wrong StaticSizeInBytes");

	protected:
		constexpr BSTSmallArrayHeapAllocator() noexcept = default;
		BSTSmallArrayHeapAllocator(const BSTSmallArrayHeapAllocator& a_rhs) = delete;
		BSTSmallArrayHeapAllocator(BSTSmallArrayHeapAllocator&& other) = delete;
		~BSTSmallArrayHeapAllocator() noexcept = default;  // BSTArray deallocated & destroyed
		BSTSmallArrayHeapAllocator& operator=(const BSTSmallArrayHeapAllocator& a_rhs) = delete;
		BSTSmallArrayHeapAllocator& operator=(BSTSmallArrayHeapAllocator&& a_rhs) = delete;

		[[nodiscard]] constexpr void*       data() noexcept { return local() ? data_local() : _data.heap; }
		[[nodiscard]] constexpr const void* data() const noexcept
		{
			return local() ? reinterpret_cast<const void*>(data_local()) : _data.heap;
		}
		[[nodiscard]] constexpr size_type capacity() const noexcept { return _capacity; }

		[[nodiscard]] traits_info Allocate(size_type count, size_type a_elem_size)
		{
			assert(count > 0 && "Allocate with 0 count");
			assert(a_elem_size == elem_size);
			if (count <= static_capacity) {
				return get_local_traits();
			} else {
				return { allocate_and_check(count * elem_size), count };
			}
		}

		void* AllocateAndRemember(size_type count, size_type a_elem_size) { return set_traits(Allocate(count, a_elem_size)); }

		// must be returned by Allocate
		void SetTraits(traits_info info) { set_traits(std::move(info)); }

		void Deallocate(void* ptr)
		{
			if (ptr != data_local()) {
				free(ptr);
			}
		}

		void Deallocate()
		{
			if (!local()) {
				free(_data.heap);
			}

			set_traits(get_local_traits());
		}

		// assume there is enough space
		static void swap_elements(pointer left, pointer right, size_type left_size, size_type right_size)
		{
			const size_type min_size = std::min(left_size, right_size);
			for (size_type i = 0; i < min_size; ++i) {
				if constexpr (std::is_move_assignable_v<value_type>) {
					value_type temp = std::move(left[i]);
					left[i] = std::move(right[i]);
					right[i] = std::move(temp);
				} else {
					value_type temp = std::move(left[i]);
					std::destroy_at(left + i);
					std::construct_at(left + i, std::move(right[i]));
					std::destroy_at(right + i);
					std::construct_at(right + i, std::move(temp));
				}
			}

			for (size_type i = min_size; i < left_size; ++i) {
				std::construct_at(right + i, std::move(left[i]));
				std::destroy_at(left + i);
			}
			for (size_type i = min_size; i < right_size; ++i) {
				std::construct_at(left + i, std::move(right[i]));
				std::destroy_at(right + i);
			}
		}

		static void swap(BSTSmallArrayHeapAllocator& left, const BSTArrayBase& left_size, BSTSmallArrayHeapAllocator& right,
			const BSTArrayBase& right_size)
		{
			if (left.local() && right.local()) {
				swap_elements(left.data_typed(), right.data_typed(), left_size.size(), right_size.size());
			} else if (!left.local() && !right.local()) {
				void* temp_ptr = left._data.heap;
				left._data.heap = right._data.heap;
				right._data.heap = temp_ptr;

				uint32_t tmp = left._capacity;
				left._capacity = right._capacity;
				right._capacity = tmp;
			} else {
				BSTSmallArrayHeapAllocator& local_alloc = left.local() ? left : right;
				BSTSmallArrayHeapAllocator& heap_alloc = left.local() ? right : left;
				const BSTArrayBase&         local_size = left.local() ? left_size : right_size;

				void*     heap_data = heap_alloc._data.heap;
				size_type heap_capacity = heap_alloc.capacity();
				pointer   local_data = local_alloc.data_typed();
				pointer   heap_alloc_local = heap_alloc.data_local();

				for (size_type i = 0; i < local_size.size(); ++i) {
					std::construct_at(heap_alloc_local + i, std::move(local_data[i]));
					std::destroy_at(local_data + i);
				}
				heap_alloc.set_traits_local();
				local_alloc.set_traits({ heap_data, heap_capacity });
			}
		}

	private:
		union Data
		{
			void* heap;
			char  local[StaticSizeInBytes]{};
		};

		[[nodiscard]] constexpr bool          local() const noexcept { return _local != 0; }
		[[nodiscard]] constexpr pointer       data_local() noexcept { return reinterpret_cast<pointer>(_data.local); }
		[[nodiscard]] constexpr const_pointer data_local() const noexcept { return reinterpret_cast<const_pointer>(_data.local); }
		[[nodiscard]] constexpr pointer       data_typed() noexcept { return static_cast<pointer>(data()); }

		// then assume it is not nullptr
		void* allocate_and_check(size_type bytes)
		{
			auto mem = malloc(bytes);
			if (!mem) {
				assert(false && "OOM");
				stl::report_and_fail("out of memory"sv);
			}
			return mem;
		}

		constexpr void* set_traits(traits_info info) noexcept
		{
			if (info.first == data_local()) {
				_local = 1;
				assert(info.second == static_capacity);
			} else {
				_local = 0;
				_data.heap = info.first;
			}
			_capacity = info.second;

			return data();
		}

		constexpr void* set_traits_local() { return set_traits(get_local_traits()); }

		constexpr traits_info get_local_traits() { return { data_local(), static_capacity }; }

		// members
		uint32_t _capacity: 31 { static_capacity };  // 00
		uint32_t _local: 1 { 1 };                    // 00
		Data     _data;                              // 08
	};

	class BSScrapArrayAllocator
	{
		// invariant: data == nullptr <=> cap == 0
		using size_type = typename BSTArrayBase::size_type;
		using traits_info = std::pair<void*, size_type>;

	protected:
		constexpr BSScrapArrayAllocator() noexcept = default;
		BSScrapArrayAllocator(const BSScrapArrayAllocator& other) = delete;
		BSScrapArrayAllocator(BSScrapArrayAllocator&& other) = delete;
		~BSScrapArrayAllocator() = default;  // BSTArray deallocated & destroyed
		BSScrapArrayAllocator& operator=(const BSScrapArrayAllocator& other) = delete;
		BSScrapArrayAllocator& operator=(BSScrapArrayAllocator&& other) = delete;

		[[nodiscard]] constexpr void*       data() noexcept { return _data; }
		[[nodiscard]] constexpr const void* data() const noexcept { return _data; }
		[[nodiscard]] constexpr size_type   capacity() const noexcept { return _capacity; }

	protected:
		[[nodiscard]] traits_info Allocate(size_type count, size_type elem_size)
		{
			assert(count > 0 && "Allocate with 0 count");
			return { allocate_and_check(count * elem_size), count };
		}

		void* AllocateAndRemember(size_type count, size_type elem_size) { return set_traits(Allocate(count, elem_size)); }

		// must be returned by Allocate
		void SetTraits(traits_info info) { set_traits(std::move(info)); }

		void Deallocate(void* ptr)
		{
			if (ptr) {
				assert(_allocator && "Deallocate: no allocator");
				_allocator->Deallocate(ptr);
			}
		}

		void Deallocate()
		{
			if (_data) {
				assert(_allocator && "Deallocate: no allocator");
				_allocator->Deallocate(_data);
			}
			set_traits({ nullptr, 0 });
			_allocator = nullptr;
		}

		static void swap(BSScrapArrayAllocator& left, const BSTArrayBase&, BSScrapArrayAllocator& right, const BSTArrayBase&)
		{
			std::swap(left._allocator, right._allocator);
			std::swap(left._data, right._data);
			std::swap(left._capacity, right._capacity);
		}

	private:
		// then assume it is not nullptr
		void* allocate_and_check(size_type bytes)
		{
			if (!_allocator) {
				auto heap = MemoryManager::GetSingleton();
				_allocator = heap ? heap->GetThreadScrapHeap() : nullptr;
				assert(_allocator);
			}

			auto mem = _allocator->Allocate(bytes, alignof(void*));
			if (!mem) {
				stl::report_and_fail("out of memory"sv);
			}
			return mem;
		}

		constexpr void* set_traits(traits_info info) noexcept
		{
			_data = info.first;
			_capacity = info.second;

			return _data;
		}

		// members
		ScrapHeap* _allocator{ nullptr };   // 00
		void*      _data{ nullptr };        // 08
		uint32_t   _capacity{ 0 };          // 10 - number of elements (not bytes)
		uint32_t   pad14 [[maybe_unused]];  // 14
	};
	static_assert(sizeof(BSScrapArrayAllocator) == 0x18);

	template <typename T, typename Allocator = BSTArrayHeapAllocator>
	class BSTArray : public Allocator, public BSTArrayBase
	{
	public:
		using allocator_type = Allocator;
		using size_type = typename BSTArrayBase::size_type;
		using value_type = T;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = pointer;
		using const_iterator = const_pointer;
		using traits_info = std::pair<pointer, size_type>;

		BSTArray() = default;

		BSTArray(size_type count) { ctor_helper(count); }

		BSTArray(size_type count, const value_type& val) { ctor_helper(count, val); }

		BSTArray(const BSTArray& other)
		{
			if (other.empty())
				return;

			auto count = other.size();
			auto ptr = allocate_remember(count);
			for (size_type i = 0; i < count; i++) {
				std::construct_at(ptr + i, other[i]);
			}
			set_size(count);
		}

		BSTArray(BSTArray&& other) noexcept :
			Allocator(), BSTArrayBase() { swap(*this, other); }

		~BSTArray() noexcept { destroy_and_free(data(), size()); }

		BSTArray& operator=(const BSTArray& other)
		{
			if (this != std::addressof(other)) {
				BSTArray tmp(other);
				swap(*this, tmp);
			}
			return *this;
		}

		BSTArray& operator=(BSTArray&& other) noexcept
		{
			if (this == std::addressof(other)) {
				return *this;
			}

			swap(*this, other);
			return *this;
		}

		void resize(size_type count) { resize_helper(count); }

		void resize(size_type count, const value_type& val) { resize_helper(count, val); }

		void reserve(size_type new_cap)
		{
			if (capacity() >= new_cap)
				return;

			auto cur_count = size();
			auto old_ptr = data();
			auto new_traits = allocate(new_cap);
			move_and_destroy(new_traits.first, old_ptr, cur_count);
			this->SetTraits(std::move(new_traits));
		}

		void clear() noexcept { resize(0); }

		reference emplace_back(auto&&... args)
		{
			auto cur_count = size();
			if (capacity() > cur_count) {
				std::construct_at(data() + cur_count, std::forward<decltype(args)>(args)...);
			} else {
				auto old_ptr = data();
				auto [new_ptr, new_cap] = allocate(std::max(4u, capacity() * 2));
				std::construct_at(new_ptr + cur_count, std::forward<decltype(args)>(args)...);
				move_and_destroy(new_ptr, old_ptr, cur_count);
				this->SetTraits({ new_ptr, new_cap });
			}
			set_size(cur_count + 1);
			return back();
		}

		void push_back(const value_type& val) { emplace_back(val); }

		void push_back(value_type&& val) { emplace_back(std::move(val)); }

		void pop_back()
		{
			assert(!empty() && "pop_back on empty vector");
			std::destroy_at(data() + size() - 1);
			set_size(size() - 1);
		}

		iterator erase(const_iterator a_pos)
		{
			iterator pos = begin() + std::distance(cbegin(), a_pos);

			if (pos == end()) {
				return end();
			}

			std::move(pos + 1, end(), pos);
			pop_back();

			return pos;
		}

		void shrink_to_fit()
		{
			auto cur_count = size();
			if (cur_count == 0) {
				this->Deallocate();
			} else if (capacity() > cur_count) {
				auto old_ptr = data();
				// impossible switch from local to heap, so we can update traits here
				auto ptr = allocate_remember(cur_count);
				move_and_destroy(ptr, old_ptr, cur_count);
			}
		}

		[[nodiscard]] constexpr reference operator[](size_type a_pos) noexcept
		{
			assert(a_pos < size());
			return data()[a_pos];
		}

		[[nodiscard]] constexpr const_reference operator[](size_type a_pos) const noexcept
		{
			assert(a_pos < size());
			return data()[a_pos];
		}

		[[nodiscard]] constexpr reference       front() noexcept { return operator[](0); }
		[[nodiscard]] constexpr const_reference front() const noexcept { return operator[](0); }

		[[nodiscard]] constexpr reference       back() noexcept { return operator[](size() - 1); }
		[[nodiscard]] constexpr const_reference back() const noexcept { return operator[](size() - 1); }

		[[nodiscard]] constexpr pointer       data() noexcept { return static_cast<pointer>(allocator_type::data()); }
		[[nodiscard]] constexpr const_pointer data() const noexcept { return static_cast<const_pointer>(allocator_type::data()); }
		[[nodiscard]] constexpr size_type     capacity() const noexcept { return allocator_type::capacity(); }

		[[nodiscard]] constexpr iterator       begin() noexcept { return data(); }
		[[nodiscard]] constexpr const_iterator begin() const noexcept { return data(); }
		[[nodiscard]] constexpr const_iterator cbegin() const noexcept { return begin(); }

		[[nodiscard]] constexpr iterator       end() noexcept { return data() + size(); }
		[[nodiscard]] constexpr const_iterator end() const noexcept { return data() + size(); }
		[[nodiscard]] constexpr const_iterator cend() const noexcept { return end(); }

	private:
		void ctor_helper(size_type count, auto&&... mb_val)
		{
			auto ptr = allocate_remember(count);
			for (size_type i = 0; i < count; i++) {
				std::construct_at(ptr + i, std::forward<decltype(mb_val)>(mb_val)...);
			}
			set_size(count);
		}

		void resize_helper(size_type count)
		{
			auto cur_count = size();
			if (cur_count >= count) {
				std::destroy_n(data() + count, cur_count - count);
			} else {
				if (capacity() >= count) {
					std::uninitialized_value_construct_n(data() + cur_count, count - cur_count);
				} else {
					auto old_ptr = data();
					auto [new_ptr, new_cap] = allocate(count);
					std::uninitialized_value_construct_n(new_ptr + cur_count, count - cur_count);
					move_and_destroy(new_ptr, old_ptr, cur_count);
					this->SetTraits({ new_ptr, new_cap });
				}
			}
			set_size(count);
		}

		void resize_helper(size_type count, auto&& val)
		{
			auto cur_count = size();
			if (cur_count >= count) {
				std::destroy_n(data() + count, cur_count - count);
			} else {
				if (capacity() >= count) {
					std::uninitialized_fill_n(data() + cur_count, count - cur_count, std::forward<decltype(val)>(val));
				} else {
					auto old_ptr = data();
					auto [new_ptr, new_cap] = allocate(count);
					std::uninitialized_fill_n(new_ptr + cur_count, count - cur_count, std::forward<decltype(val)>(val));
					move_and_destroy(new_ptr, old_ptr, cur_count);
					this->SetTraits({ new_ptr, new_cap });
				}
			}
			set_size(count);
		}

		static void swap(BSTArray& first, BSTArray& second) noexcept
		{
			Allocator::swap(first, first, second, second);
			BSTArrayBase::swap(first, second);
		}

		void move_and_destroy(pointer new_ptr, pointer old_ptr, size_type count) noexcept(std::is_nothrow_destructible_v<value_type>)
		{
			// smallarray check
			if (new_ptr == old_ptr)
				return;

			if constexpr (std::is_trivially_copyable_v<value_type>) {
				std::memcpy(new_ptr, old_ptr, count * sizeof(value_type));
			} else {
				std::uninitialized_move_n(old_ptr, count, new_ptr);
			}

			destroy_and_free(old_ptr, count);
		}

		void destroy_and_free(pointer ptr, size_type size) noexcept(std::is_nothrow_destructible_v<value_type>)
		{
			std::destroy_n(ptr, size);
			this->Deallocate(ptr);
		}

		traits_info allocate(size_type count)
		{
			auto [ptr, cap] = this->Allocate(count, sizeof(value_type));
			return { static_cast<pointer>(ptr), cap };
		}

		pointer allocate_remember(size_type count)
		{
			return static_cast<pointer>(this->AllocateAndRemember(count, sizeof(value_type)));
		}
	};

	template <class T, uint32_t N = 1>
	using BSTSmallArray = BSTArray<T, BSTSmallArrayHeapAllocator<T, sizeof(T) * N>>;

	template <class T>
	using BSScrapArray = BSTArray<T, BSScrapArrayAllocator>;

	template <class T>
	class BSStaticArray
	{
	public:
		using value_type = T;
		using size_type = std::uint32_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = pointer;
		using const_iterator = const_pointer;

		[[nodiscard]] constexpr reference operator[](size_type a_pos) noexcept
		{
			assert(a_pos < _size);
			return _data[a_pos];
		}

		[[nodiscard]] constexpr const_reference operator[](size_type a_pos) const noexcept
		{
			assert(a_pos < _size);
			return _data[a_pos];
		}

		[[nodiscard]] constexpr reference       front() noexcept { return operator[](0); }
		[[nodiscard]] constexpr const_reference front() const noexcept { return operator[](0); }

		[[nodiscard]] constexpr reference       back() noexcept { return operator[](size() - 1); }
		[[nodiscard]] constexpr const_reference back() const noexcept { return operator[](size() - 1); }

		[[nodiscard]] constexpr pointer       data() noexcept { return _data; }
		[[nodiscard]] constexpr const_pointer data() const noexcept { return _data; }

		[[nodiscard]] constexpr iterator       begin() noexcept { return empty() ? nullptr : data(); }
		[[nodiscard]] constexpr const_iterator begin() const noexcept { return empty() ? nullptr : data(); }
		[[nodiscard]] constexpr const_iterator cbegin() const noexcept { return begin(); }

		[[nodiscard]] constexpr iterator       end() noexcept { return empty() ? nullptr : data() + size(); }
		[[nodiscard]] constexpr const_iterator end() const noexcept { return empty() ? nullptr : data() + size(); }
		[[nodiscard]] constexpr const_iterator cend() const noexcept { return end(); }

		[[nodiscard]] constexpr bool empty() const noexcept { return size() == 0; }

		[[nodiscard]] constexpr size_type size() const noexcept { return _size; }

	private:
		// members
		pointer       _data{ nullptr };  // 00
		std::uint32_t _size{ 0 };        // 08
	};

	template <class T>
	class BSTSmallSharedArray
	{
	public:
		using value_type = T;
		using size_type = std::uint32_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = pointer;
		using const_iterator = const_pointer;

		[[nodiscard]] inline reference operator[](size_type a_pos) noexcept
		{
			assert(a_pos < _size);
			return data()[a_pos];
		}

		[[nodiscard]] inline const_reference operator[](size_type a_pos) const noexcept
		{
			assert(a_pos < _size);
			return data()[a_pos];
		}

		[[nodiscard]] inline pointer data() noexcept
		{
			return size() > 1 ? _data.heap : std::addressof(_data.local);
		}

		[[nodiscard]] inline const_pointer data() const noexcept
		{
			return size() > 1 ? _data.heap : std::addressof(_data.local);
		}

		[[nodiscard]] inline iterator       begin() noexcept { return data(); }
		[[nodiscard]] inline const_iterator begin() const noexcept { return data(); }
		[[nodiscard]] inline const_iterator cbegin() const noexcept { return begin(); }

		[[nodiscard]] inline iterator       end() noexcept { return data() + size(); }
		[[nodiscard]] inline const_iterator end() const noexcept { return data() + size(); }
		[[nodiscard]] inline const_iterator cend() const noexcept { return end(); }

		[[nodiscard]] constexpr bool empty() const noexcept { return size() != 0; }

		[[nodiscard]] constexpr size_type size() const noexcept { return _size; }

	private:
		union Data
		{
			~Data(){};

			pointer    heap{ 0 };
			value_type local;
		};

		// members
		std::uint32_t _size{ 0 };  // 00
		Data          _data;       // 08
	};
}
