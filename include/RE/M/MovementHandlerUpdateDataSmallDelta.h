#pragma once

#include "RE/B/BSTArray.h"
#include "RE/M/MovementVector.h"

namespace RE
{
	struct MovementHandlerUpdateDataSmallDelta
	{
		// members
		BSScrapArray<void*> array2;          // 00
		BSScrapArray<void*> array1;          // 20
		MovementVector      direction;       // 40
		NiPoint3            looking_angles;  // 50
		uint8_t             field_5C;        // 5C
		uint8_t             pad5D[3];        // 5D
		float               field_60;        // 60
		float               field_64;        // 64
		uint8_t             field68;         // 68
		uint8_t             pad69[3];        // 69
		float               dtime;           // 6C
		float               acc;             // 70 - denorm
		float               decel;           // 74 - denorm
		float               min_rot_speed;   // 78 - denorm
		float               max_rot_speed;   // 7C - denorm
		float               rot_speed;       // 80
		uint8_t             pad84[4];        // 84
	};
	static_assert(sizeof(MovementHandlerUpdateDataSmallDelta) == 0x88);
}
