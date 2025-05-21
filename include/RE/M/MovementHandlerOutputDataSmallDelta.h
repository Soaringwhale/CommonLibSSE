#pragma once

#include "RE/M/MovementVector.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	struct MovementHandlerOutputDataSmallDelta
	{
		// members
		MovementVector MovementDirection;  // 00
		NiPoint3       rot_speed;          // 10
		float          time;               // 1C
	};
	static_assert(sizeof(MovementHandlerOutputDataSmallDelta) == 0x20);
}
