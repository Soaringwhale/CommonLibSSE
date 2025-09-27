#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkbEvent.h"
#include "RE/H/hkbModifier.h"
#include "RE/H/hkpContactListener.h"

namespace RE
{
	class hkbBoneIndexArray;
	class hkpRigidBody;

	class BSRagdollContactListenerModifier : public hkbModifier, public hkpContactListener
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSRagdollContactListenerModifier;
		inline static constexpr auto VTABLE = VTABLE_BSRagdollContactListenerModifier;

		// members
		hkbEventProperty       contactEvent;        // 58
		hkbBoneIndexArray*     bones;               // 68
		bool                   throwEvent;          // 70
		uint8_t                pad71[7];            // 71
		hkArray<hkpRigidBody*> ragdollRigidBodies;  // 78
	};
	static_assert(sizeof(BSRagdollContactListenerModifier) == 0x88);
}
