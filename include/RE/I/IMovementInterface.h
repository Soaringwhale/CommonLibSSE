#pragma once

namespace RE
{
	struct IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementInterface;

		virtual ~IMovementInterface();
	};
	static_assert(sizeof(IMovementInterface) == 0x8);
}
