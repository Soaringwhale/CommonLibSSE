#pragma once

namespace RE
{
	/// Intermediate value for pointer return values. To avoid a resource leak,
	/// it needs to have a reference removed when the object is no longer needed.
	/// Usually this type is used as an intermediate return value for functions and will
	/// be assigned directly to a hkRefPtr.
	/// Note that this indicates a newly added reference, not necessarily a new object, i.e.
	/// the returned object may be shared.
	template <typename T>
	class hkRefNew
	{
	public:
		/// Implicit conversion from raw pointer.
		hkRefNew(T* t) :
			m_pntr(t) {}

		/// Assume ownership of this reference.
		/// Assumes responsibility for calling removeReference in the future.
		T* stealOwnership()
		{
			T* t = m_pntr;
			m_pntr = nullptr;
			return t;
		}

	private:
		hkRefNew();                         ///< Not implemented
		void operator=(const hkRefNew& b);  ///< Not implemented
	public:
		// members
		T* m_pntr;  // 00
	};

	template <class T>
	class hkRefPtr
	{
	public:
		using element_type = T;

		// 1
		inline constexpr hkRefPtr() noexcept :
			_ptr(nullptr)
		{}

		// 2
		inline constexpr hkRefPtr(std::nullptr_t) noexcept :
			_ptr(nullptr)
		{}

		// 3
		template <
			class Y,
			std::enable_if_t<
				std::is_convertible_v<
					Y*,
					element_type*>,
				int> = 0>
		inline explicit hkRefPtr(Y* a_rhs) :
			_ptr(a_rhs)
		{
			TryAttach();
		}

		// 9a
		inline hkRefPtr(const hkRefPtr& a_rhs) :
			_ptr(a_rhs._ptr)
		{
			TryAttach();
		}

		// 9b
		template <
			class Y,
			std::enable_if_t<
				std::is_convertible_v<
					Y*,
					element_type*>,
				int> = 0>
		inline hkRefPtr(const hkRefPtr<Y>& a_rhs) :
			_ptr(a_rhs._ptr)
		{
			TryAttach();
		}

		// 10a
		inline hkRefPtr(hkRefPtr&& a_rhs) noexcept :
			_ptr(std::move(a_rhs._ptr))
		{
			a_rhs._ptr = nullptr;
		}

		// 10b
		template <
			class Y,
			std::enable_if_t<
				std::is_convertible_v<
					Y*,
					element_type*>,
				int> = 0>
		inline hkRefPtr(hkRefPtr<Y>&& a_rhs) noexcept :
			_ptr(std::move(a_rhs._ptr))
		{
			a_rhs._ptr = nullptr;
		}

		/// Steal (don't increment) the reference from 'rp'.
		//hkRefPtr(hkRefNew<T> rp) :
		//	_ptr(rp.stealOwnership())
		//{
		//}

		inline ~hkRefPtr()
		{
			TryDetach();
		}

		// 1a
		inline hkRefPtr& operator=(const hkRefPtr& a_rhs)
		{
			if (this != std::addressof(a_rhs)) {
				TryDetach();
				_ptr = a_rhs._ptr;
				TryAttach();
			}
			return *this;
		}

		// 1b
		template <
			class Y,
			std::enable_if_t<
				std::is_convertible_v<
					Y*,
					element_type*>,
				int> = 0>
		inline hkRefPtr& operator=(const hkRefPtr<Y>& a_rhs)
		{
			TryDetach();
			_ptr = a_rhs._ptr;
			TryAttach();
			return *this;
		}

		// 2a
		inline hkRefPtr& operator=(hkRefPtr&& a_rhs)
		{
			if (this != std::addressof(a_rhs)) {
				TryDetach();
				_ptr = std::move(a_rhs._ptr);
				a_rhs._ptr = nullptr;
			}
			return *this;
		}

		// 2b
		template <
			class Y,
			std::enable_if_t<
				std::is_convertible_v<
					Y*,
					element_type*>,
				int> = 0>
		inline hkRefPtr& operator=(hkRefPtr<Y>&& a_rhs)
		{
			TryDetach();
			_ptr = std::move(a_rhs._ptr);
			a_rhs._ptr = nullptr;
			return *this;
		}

		/// Assignment operator.
		/// Steals (does not increment) the reference from 'rp'.
		/// Decrease the original reference count and set pointer to object from 'rp'.
		//void operator=(hkRefNew<T> rp)
		//
		//{
		//	_ptr = rp.stealOwnership();
		//	return *this;
		//}

		inline void reset()
		{
			TryDetach();
		}

		template <
			class Y,
			std::enable_if_t<
				std::is_convertible_v<
					Y*,
					element_type*>,
				int> = 0>
		inline void reset(Y* a_ptr)
		{
			if (_ptr != a_ptr) {
				TryDetach();
				_ptr = a_ptr;
				TryAttach();
			}
		}

		[[nodiscard]] constexpr element_type* get() const noexcept
		{
			return _ptr;
		}

		[[nodiscard]] explicit constexpr operator bool() const noexcept
		{
			return static_cast<bool>(_ptr);
		}

		[[nodiscard]] constexpr element_type& operator*() const noexcept
		{
			assert(static_cast<bool>(*this));
			return *_ptr;
		}

		[[nodiscard]] constexpr element_type* operator->() const noexcept
		{
			assert(static_cast<bool>(*this));
			return _ptr;
		}

	protected:
		template <class>
		friend class hkRefPtr;

		void TryAttach()
		{
			if (_ptr) {
				_ptr->AddReference();
			}
		}

		void TryDetach()
		{
			if (_ptr) {
				_ptr->RemoveReference();
				_ptr = nullptr;
			}
		}

		// members
		element_type* _ptr;  // 0
	};
	static_assert(sizeof(hkRefPtr<void*>) == 0x8);

	template <class T, class... Args>
	[[nodiscard]] inline hkRefPtr<T> make_hkref(Args&&... a_args)
	{
		return hkRefPtr<T>{ new T(std::forward<Args>(a_args)...) };
	}

	template <class T1, class T2>
	[[nodiscard]] constexpr bool operator==(const hkRefPtr<T1>& a_lhs, const hkRefPtr<T2>& a_rhs)
	{
		return a_lhs.get() == a_rhs.get();
	}

	template <class T1, class T2>
	[[nodiscard]] constexpr bool operator!=(const hkRefPtr<T1>& a_lhs, const hkRefPtr<T2>& a_rhs)
	{
		return !(a_lhs == a_rhs);
	}

	template <class T>
	[[nodiscard]] constexpr bool operator==(const hkRefPtr<T>& a_lhs, std::nullptr_t) noexcept
	{
		return !a_lhs;
	}

	template <class T>
	[[nodiscard]] constexpr bool operator==(std::nullptr_t, const hkRefPtr<T>& a_rhs) noexcept
	{
		return !a_rhs;
	}

	template <class T>
	[[nodiscard]] constexpr bool operator!=(const hkRefPtr<T>& a_lhs, std::nullptr_t) noexcept
	{
		return static_cast<bool>(a_lhs);
	}

	template <class T>
	[[nodiscard]] constexpr bool operator!=(std::nullptr_t, const hkRefPtr<T>& a_rhs) noexcept
	{
		return static_cast<bool>(a_rhs);
	}

	template <class T>
	hkRefPtr(T*) -> hkRefPtr<T>;

	/// Scoped pointer to an object. This is a simple container to hold objects that can not exist on the stack.
	/// The object is allocated using new() and the default constructor, and delete()'ed on the hkScopedPtr going
	/// out of scope.
	/// Pointer operators * and -> are overridden to function transparently
	template <typename T>
	class hkScopedPtr
	{
	public:
		typedef hkScopedPtr<T> ThisType;

		/// Create a new hkScopedPtr, calling the object's default constructor
		hkScopedPtr() { m_object = new T; }
		/// Pass in an already constructed object. The hkScopedPtr now owns this object
		hkScopedPtr(T* assignIn) { m_object = assignIn; }
		~hkScopedPtr() { delete m_object; }

		const T* get() const { return m_object; }
		T*       get() { return m_object; }

		operator T*() { return m_object; }
		operator const T*() const { return m_object; }

		const T& operator*() const { return *m_object; }
		T&       operator*() { return *m_object; }

		const T* operator->() const { return m_object; }
		T*       operator->() { return m_object; }

		// members
		T* m_object;  // 00

	private:
		// hkScopedPtr is not copyable or assignable
		hkScopedPtr(const hkScopedPtr<T>& copyIn) { assert(false); }
		hkScopedPtr<T>& operator=(const hkScopedPtr<T>& copyIn)
		{
			assert(false);
			return *this;
		}
	};
}
