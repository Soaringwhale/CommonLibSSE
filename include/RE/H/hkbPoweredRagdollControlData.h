#pragma once

namespace RE
{
	/// The controls that influence the behavior of an hkbPoweredRagdollModifier.
	struct hkbPoweredRagdollControlData
	{
	public:
		// members
		float   maxForce;                      // 00 - The maximum force to apply.
		float   tau;                           // 04 - The relative motor stiffness between 0 and 1.
		float   damping;                       // 08 - The relative motor damping between 0 and 1.
		float   proportionalRecoveryVelocity;  // 0C - A factor to the current error to calculate the recovery velocity of the motors.
		float   constantRecoveryVelocity;      // 10 - A constant velocity which is used by the motors to recover from errors.
		uint8_t pad14[12];                     // 20
	};
	static_assert(sizeof(hkbPoweredRagdollControlData) == 0x20);
}
