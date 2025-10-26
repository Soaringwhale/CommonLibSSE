#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkQuaternion.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkVector4.h"
#include "RE/H/hkbModifier.h"

namespace RE
{
	class hkbBoneIndexArray;

	/// This modifier allows you to specify which bones are keyframed. One float per bone is placed
	/// into the track data. This data is passed through the behavior graph and can be blended by
	/// blend nodes and during transitions. The track data is used by hkbPoweredRagdollModifier
	/// and hkbRigidBodyRagdollModifier to decide which bones should be keyframed.
	class hkbKeyframeBonesModifier : public hkbModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbKeyframeBonesModifier;
		inline static constexpr auto VTABLE = VTABLE_hkbKeyframeBonesModifier;

		/// One keyframe info for each ragdoll bone that needs to be keyframed with an explicit target.
		struct KeyframeInfo
		{
			// members
			hkVector4    keyframedPosition;  // 00 - The position of the keyframed bone.
			hkQuaternion keyframedRotation;  // 10 - The orientation of the keyframed bone.
			int16_t      boneIndex;          // 20 - The ragdoll bone to be keyframed.
			bool         isValid;            // 22 - Whether or not m_keyframedPosition and m_keyframedRotation are valid.
		};
		static_assert(sizeof(KeyframeInfo) == 0x30);

		// members
		hkArray<KeyframeInfo>       keyframeInfo;        // 50 - The list of bones to be keyframed with an explicit target.
		hkRefPtr<hkbBoneIndexArray> keyframedBonesList;  // 60 - Keyframed bone list that HAT can set.
	};
	static_assert(sizeof(hkbKeyframeBonesModifier) == 0x68);
}
