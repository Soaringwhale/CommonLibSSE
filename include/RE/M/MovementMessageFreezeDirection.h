#pragma once

#include "RE/M/MovementMessage.h"

namespace RE
{
	class MovementMessageFreezeDirection : public MovementMessage
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessageFreezeDirection;
		inline static constexpr auto VTABLE = VTABLE_MovementMessageFreezeDirection;

		enum class FreezeMessageType : uint32_t
		{
			Type0,
			Type1,
		};

		explicit MovementMessageFreezeDirection(FreezeMessageType a_type = FreezeMessageType::Type1) :
			type(a_type) { stl::emplace_vtable(this); }

		~MovementMessageFreezeDirection() = default;  // 00

		// override (MovementMessage)
		uint32_t GetType() const override { return 0; };                          // 01
		void     Write(BSPathingStreamWrite& stream) const override { stream; };  // 02
		void     Read(BSPathingStreamRead& stream) override { stream; };          // 03

		// members
		FreezeMessageType type{ 1 };  // 10
		uint8_t           pad14[4];   // 14
	};
	static_assert(sizeof(MovementMessageFreezeDirection) == 0x18);
}
