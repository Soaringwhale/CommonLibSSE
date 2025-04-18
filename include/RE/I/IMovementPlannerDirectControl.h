#pragma once

#include "RE/I/IMovementInterface.h"

namespace RE
{
	class IMovementPlannerDirectControl : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementPlannerDirectControl;

		~IMovementPlannerDirectControl() override;  // 00

		// add
		virtual void SetPlannerDirectControl() = 0;                      // 01
		virtual void SetTargetDirection(const NiPoint3& direction) = 0;  // 02
		virtual void SetTargetSpeed(float speed) = 0;                    // 03
		virtual void SetTargetAngle(const NiPoint3& angle) = 0;          // 04
		virtual void ClearPlannerDirectControl() = 0;                    // 05
	};
	static_assert(sizeof(IMovementPlannerDirectControl) == 0x8);
}
