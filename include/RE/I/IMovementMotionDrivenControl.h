#pragma once

#include "RE/I/IMovementInterface.h"

namespace RE
{
	class IMovementMotionDrivenControl : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementMotionDrivenControl;

		~IMovementMotionDrivenControl() override;  // 00

		// add
		virtual void OnMoveToHigh() = 0;                     // 01
		virtual void OnMoveToNotHigh() = 0;                  // 02
		virtual void SetAnimationDriven() = 0;               // 03
		virtual void SetMotionDriven() = 0;                  // 04
		virtual void SetAnimationDrivenAllowRotation() = 0;  // 05
		virtual bool GetMotionDriven() = 0;                  // 06
		virtual bool GetAnimationDriven() = 0;               // 07
		virtual bool GetAllowRotation() = 0;                 // 08
	};
	static_assert(sizeof(IMovementMotionDrivenControl) == 0x8);
}
