#pragma once

namespace RE
{
	struct IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementInterface;
		inline static constexpr auto VTABLE = VTABLE_IMovementInterface;

		IMovementInterface() { stl::emplace_vtable(this); }

		virtual ~IMovementInterface() = default;  // 00
	};
	static_assert(sizeof(IMovementInterface) == 0x8);
}
