#pragma once

#include "RE/H/hkVector4.h"
#include "RE/H/hkbModifier.h"

namespace RE
{
	/// This is a modifier that uses a PID controller to provide variable damping.
	class hkbDampingModifier : public hkbModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbDampingModifier;
		inline static constexpr auto VTABLE = VTABLE_hkbDampingModifier;

		// members
		float     kP;                   // 50 - The coefficient for the proportional component of the damping system.
		float     kI;                   // 54 - The coefficient for the integral component of the damping system.
		float     kD;                   // 58 - The coefficient for the derivative component of the damping system.
		bool      enableScalarDamping;  // 5C - Enable/disable scalar damping.
		bool      enableVectorDamping;  // 5D - Enable/disable Vector4 damping.
		uint8_t   pad5E[2];             // 5E
		float     rawValue;             // 60 - The value that is being damped.
		float     dampedValue;          // 64 - The resulting damped value.
		uint8_t   pad68[8];             // 68
		hkVector4 rawVector;            // 70 - The vector being damped.
		hkVector4 dampedVector;         // 80 - The resulting damped vector.
		hkVector4 vecErrorSum;          // 90 - The sum of errors so far for the damped vector.
		hkVector4 vecPreviousError;     // A0 - The previous error for the damped vector.
		float     errorSum;             // B0 - The sum of the errors so far.
		float     previousError;        // B4 - The previous error.
		uint8_t   padB8[8];             // B8
	};
	static_assert(sizeof(hkbDampingModifier) == 0xC0);
}
