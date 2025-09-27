#pragma once

#include "RE/H/hkRefPtr.h"
#include "RE/H/hkbModifier.h"
#include "RE/H/hkbRigidBodyRagdollControlData.h"

namespace RE
{
	class hkbBoneIndexArray;

	/// Produces control data used by hkbRigidBodyRagdollModifier and puts it into
	/// the tracks of the output when modify() is called.  This data is passed
	/// through the behavior tree and can be blended by blend nodes and during transitions.
	class hkbRigidBodyRagdollControlsModifier : public hkbModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbRigidBodyRagdollControlsModifier;
		inline static constexpr auto VTABLE = VTABLE_hkbRigidBodyRagdollControlsModifier;

		// members
		hkbRigidBodyRagdollControlData controlData;  // 50
		hkRefPtr<hkbBoneIndexArray>    bones;        // 90
		uint8_t                        pad98[8];     // 98
	};
	static_assert(sizeof(hkbRigidBodyRagdollControlsModifier) == 0x60);
}
