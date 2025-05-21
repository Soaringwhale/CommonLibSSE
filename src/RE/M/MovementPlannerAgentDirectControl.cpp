#include "RE/M/MovementPlannerAgentDirectControl.h"

namespace RE
{
	NiPoint3 RE::MovementPlannerAgentDirectControl::GetTargetDirection() const
	{
		BSReadLockGuard g(lock);
		auto            ans = targetDirection;
		return ans;
	}

	float MovementPlannerAgentDirectControl::GetTargetSpeed() const
	{
		BSReadLockGuard g(lock);
		auto            ans = targetSpeed;
		return ans;
	}

	NiPoint3 MovementPlannerAgentDirectControl::GetTargetAngle() const
	{
		BSReadLockGuard g(lock);
		auto            ans = targetAngle;
		return ans;
	}
}
