#pragma once

#include "RE/H/hkVector4.h"
#include "RE/H/hkbModifier.h"

namespace RE
{
	/// Gradually aligns the up-vector of the character's world-from-model transform
	/// with the world up-vector.  This is useful when the character is getting
	/// up after having been a ragdoll.  When using the hkbPoweredRagdollModifier
	/// the world-from-model of the character is typically allowed to rotate
	/// freely.  But when you want the character to stand up again, the world-from-model
	/// needs to be realigned with the world so that the character stands up straight.
	class hkbGetUpModifier : public hkbModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbGetUpModifier;
		inline static constexpr auto VTABLE = VTABLE_hkbGetUpModifier;

		// members
		hkVector4 groundNormal;             // 50 - The character's up-vector is aligned with this vector until m_alignWithGroundDuration elapses, after which it is aligned with the world up-vector.
		float     duration;                 // 60 - Duration for aligning the character's up-vector.
		float     alignWithGroundDuration;  // 64 - Duration for which the character's up-vector is aligned with m_groundNormal, after which it is aligned with the world up-vector.
		int16_t   rootBoneIndex;            // 68 - The root (ragdoll) bone used for pose matching.  If this is -1, the index is taken from the character's hkbBoneInfo.
		int16_t   otherBoneIndex;           // 6A - A second (ragdoll) bone used for pose matching.  If this is -1, the index is taken from the character's hkbBoneInfo.
		int16_t   anotherBoneIndex;         // 6C - A third (ragdoll) bone used for pose matching.  If this is -1, the index is taken from the character's hkbBoneInfo.
		uint8_t   pad6E[2];                 // 6E
		float     timeSinceBegin;           // 70 - Time since the getup modifier begin method was called.
		float     timeStep;                 // 74 - Time slice information - used by the modify() method.
		bool      initNextModify;           // 78 - Indicates whether to compute world from model next modify.
		uint8_t   pad79[7];                 // 79
	};
	static_assert(sizeof(hkbGetUpModifier) == 0x80);
}
