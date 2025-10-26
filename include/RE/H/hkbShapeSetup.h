#pragma once

#include "RE/H/hkStringPtr.h"

namespace RE
{
	struct hkbShapeSetup
	{
		// members
		float capsuleHeight;  // 00
		float capsuleRadius;  // 04
	};
	static_assert(sizeof(hkbShapeSetup) == 0x8);
}
