#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/M/MovementPlannerAgent.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class IMovementControllerRegisterInterface;

	class MovementPlannerAgentDirectControl : public MovementPlannerAgent
	{
	public:
		NiPoint3 GetTargetDirection() const;
		float    GetTargetSpeed() const;
		NiPoint3 GetTargetAngle() const;

		// members
		IMovementControllerRegisterInterface* register_interface;  // 20
		mutable BSReadWriteLock               lock;                // 28
		NiPoint3                              targetDirection;     // 30
		float                                 targetSpeed;         // 3C
		NiPoint3                              targetAngle;         // 40
		uint8_t                               pad4C[4];            // 4C
	};
	static_assert(sizeof(MovementPlannerAgentDirectControl) == 0x50);
}
