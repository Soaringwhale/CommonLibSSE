#pragma once

#include "RE/I/IMovementInterface.h"

namespace RE
{
	class IMovementDirectControl : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementDirectControl;

		~IMovementDirectControl() override;  // 00

		// add
		virtual void SetDirectControl() = 0;                                                  // 01
		virtual void SetMovementDirection(const RE::NiPoint3& direction) = 0;                 // 02
		virtual void SetMovementSpeed(float speed) = 0;                                       // 03
		virtual void SetMovementRotationSpeed(const RE::NiPoint3& rot_speed) = 0;             // 04
		virtual void RampToMovementDirection(const RE::NiPoint3& direction, float time) = 0;  // 05
		virtual void RampToMovementSpeed(float speed, float time) = 0;                        // 06
		virtual void RampToRotationSpeed(const RE::NiPoint3& rot_speed, float time) = 0;      // 07
		virtual void ClearDirectControl() = 0;                                                // 08
	};
	static_assert(sizeof(IMovementDirectControl) == 0x8);
}
