#pragma once

namespace RE
{
	/// This struct stores data related to keyframing ragdoll rigid bodies.
	/// See controller implementations for more information on how this data is used (Eg. hkbpRagdollRigidBodyController, hkbnpRagdollRigidBodyController).
	struct hkbKeyFrameControlData
	{
		// members

		/// 00 - This parameter blends the desired target for a bone between model space (0.0) or local space (1.0).
		/// Usually the controller will be much stiffer and more stable when driving to model space.
		/// However local space targeting can look more natural.
		/// It is similar to the deprecated bone controller hierarchyGain parameter
		float hierarchyGain;

		/// 04 - This gain dampens the velocities of the bodies. The current velocity of the body is
		/// scaled by this parameter on every frame before the controller is applied. It is
		/// applied every step and is generally more aggressive than standard linear or angular damping.
		/// A value of 0 means no damping.
		float velocityDamping;

		float accelerationGain;  // 08 - This gain controls the proportion of the difference in acceleration that is applied to the bodies. It dampens the effects of the velocity control.
		float velocityGain;      // 0C - This gain controls the proportion of the difference in velocity that is applied to the bodies. It dampens the effects of the position control.

		/// 10 - This gain controls the proportion of the difference in position that is
		/// applied to the bodies. It has the most immediate effect. High gain
		/// values make the controller very stiff. Once the controller is too stiff
		/// it will tend to overshoot. The velocity gain can help control this.
		float positionGain;

		/// 14 - The position difference is scaled by the inverse delta time to compute a
		/// velocity to be applied to the rigid body. The velocity is first clamped to this
		/// limit before it is applied.
		float positionMaxLinearVelocity;

		/// 18 - The orientation difference is scaled by the inverse delta time to compute an angular
		/// velocity to be applied to the rigid body. The velocity is first clamped to this
		/// limit before it is applied.
		float positionMaxAngularVelocity;

		/// 1C - This gain allows for precise matching between keyframes and the current position.
		/// It works like the m_positionGain: it calculates an optimal
		/// \code deltaVelocity = (keyFramePosition - currentPosition) / deltaTime \endcode
		/// scales it by m_snapGain, clips it against m_snapMaxXXXVelocity and scales it down
		/// \code if (keyFramePosition - currentPosition) > m_snapMaxXXXXDistance \endcode
		float snapGain;

		float snapMaxLinearVelocity;   // 20 - See m_snapGain. The linear velocity calculated from the snapGain is clamped to this limit before being applied.
		float snapMaxAngularVelocity;  // 24 - See m_snapGain. The angular velocity calculated from the snapGain is clamped to this limit before being applied.

		/// 28 - This sets the max linear distance for the snap gain to work at full strength.
		/// The strength of the controller peaks at this distance.
		/// If the current distance is bigger than m_snapMaxLinearDistance, the snap velocity will be scaled
		/// by sqrt( maxDistane/currentDistance ).
		float snapMaxLinearDistance;

		/// 2C - This sets the max angular distance for the snap gain to work at full strength.
		/// The strength of the controller peaks at this distance.
		/// If the current distance is bigger than m_snapMaxAngularDistance, the snap velocity will be scaled
		/// by sqrt( maxDistane/currentDistance ).
		float snapMaxAngularDistance;
	};
	static_assert(sizeof(hkbKeyFrameControlData) == 0x30);

	/// The controls that influence the behavior of an hkbRigidBodyRagdollModifier.
	struct hkbRigidBodyRagdollControlData
	{
		// members
		hkbKeyFrameControlData keyFrameHierarchyControlData;  // 00 - This data governs how the rigid bodies should be keyframed

		/// 30 - When going from powered ragdoll to rigid body ragdoll,
		/// there is often a visual discontinuity.  We smooth it
		/// out by blending the current ragdoll pose with the
		/// pose being driven toward.  See hkbRagdollDriverModifier.
		float   durationToBlend;
		uint8_t pad34[12];  // 34
	};
	static_assert(sizeof(hkbRigidBodyRagdollControlData) == 0x40);
}
