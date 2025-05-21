#pragma once

#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/B/BSTSmartPointer.h"

namespace RE
{
	BSSmartPointer(IMovementParameters);
	class IMovementParameters : public BSIntrusiveRefCounted
	{
	public:
		virtual ~IMovementParameters() = default;  // 00
		virtual float    GetMaxSpeed() const;
		virtual float    GetAcceleration() const;
		virtual float    GetDeceleration() const;
		virtual float    GetAngleAcceleration() const;
		virtual float    GetRotationSpeedMult() const;
		virtual uint32_t GetType() const;
		virtual void     Write(void);
		virtual void     Read(void);
	};
	static_assert(sizeof(IMovementParameters) == 0x10);
}
