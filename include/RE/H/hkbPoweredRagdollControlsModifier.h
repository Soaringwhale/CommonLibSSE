#pragma once

#include "RE/H/hkRefPtr.h"
#include "RE/H/hkbModifier.h"
#include "RE/H/hkbPoweredRagdollControlData.h"
#include "RE/H/hkbWorldFromModelModeData.h"

namespace RE
{
	class hkbBoneIndexArray;
	class hkbBoneWeightArray;

	/// Produces control data used by hkbPoweredRagdollModifier and puts it into
	/// the tracks of the output when modify() is called.  This data is passed
	/// through the behavior tree and can be blended by blend nodes and during transitions.
	class hkbPoweredRagdollControlsModifier : public hkbModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbPoweredRagdollControlsModifier;
		inline static constexpr auto VTABLE = VTABLE_hkbPoweredRagdollControlsModifier;

		// members
		hkbPoweredRagdollControlData controlData;             // 50 - The control data for an hkbPoweredRagdollModifier.
		hkRefPtr<hkbBoneIndexArray>  bones;                   // 70 - The bones to be driven by the rigid body ragdoll controller.  If this is empty, all bones will be driven.
		hkbWorldFromModelModeData    worldFromModelModeData;  // 78 - How to process the world-from-model.
		hkRefPtr<hkbBoneWeightArray> boneWeights;             // 80 - A weight for each bone of the ragdoll.
		uint8_t                      pad88[8];                // 88
	};
	static_assert(sizeof(hkbPoweredRagdollControlsModifier) == 0x90);
}
