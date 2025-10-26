#pragma once

namespace RE
{
	template <class T>
	struct IBSTCreator
	{
	public:
		IBSTCreator() = default;

		virtual ~IBSTCreator() = default;  // 00

		// add
		[[nodiscard]] virtual T* CreateImpl() const = 0;             // 01
		virtual void             Destroy(const T* a_val) const = 0;  // 02
	};
	static_assert(sizeof(IBSTCreator<void*>) == 0x8);
}
