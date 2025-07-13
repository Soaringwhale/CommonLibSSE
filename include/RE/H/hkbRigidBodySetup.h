#pragma once

#include "RE/H/hkbShapeSetup.h"

namespace RE
{
	struct hkbRigidBodySetup
	{
		// members
		hkbShapeSetup shapeSetup;           // 00
		uint32_t      collisionFilterInfo;  // 08
	};
	static_assert(sizeof(hkbRigidBodySetup) == 0xC);
}
