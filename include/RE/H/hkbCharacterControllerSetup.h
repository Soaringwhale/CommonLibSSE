#pragma once

#include "RE/H/hkbRigidBodySetup.h"

namespace RE
{
	class hkReferencedObject;

	struct hkbCharacterControllerSetup
	{
		// members
		hkbRigidBodySetup   rigidBodySetup;   // 00
		uint8_t             pad[4];           // 0C
		hkReferencedObject* controllerCInfo;  // 10
	};
	static_assert(sizeof(hkbCharacterControllerSetup) == 0x18);
}
