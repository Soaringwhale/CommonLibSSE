#pragma once

#include "RE/I/IMovementInterface.h"
#include "RE/M/MovementMessage.h"

namespace RE
{
	class BSPathingLocation;
	class NiPoint3;

	class IMovementMessageInterface : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementMessageInterface;

		~IMovementMessageInterface() override;  // 00

		// add
		virtual void PostWarpToMessage(const BSPathingLocation& loc, const NiPoint3& P) = 0;  // 01
		virtual void PostMessageA(const MovementMessagePtr& msg) = 0;                         // 02
		virtual void SendMessageA(const MovementMessage& msg) = 0;                            // 03
	};
	static_assert(sizeof(IMovementMessageInterface) == 0x8);
}
