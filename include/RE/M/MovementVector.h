#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	class MovementVector
	{
	public:
		MovementVector() = default;

		MovementVector(const NiPoint3& a_eulerAngles, float a_speed) :
			eulerAngles(a_eulerAngles), speed(a_speed)
		{
		}

		~MovementVector() = default;
		MovementVector(const MovementVector&) = default;
		MovementVector& operator=(const MovementVector&) = default;

		const NiPoint3& QEulerAngles() const
		{
			return eulerAngles;
		}

		float QSpeed() const
		{
			return speed;
		}

		void SetEulerAngles(const RE::NiPoint3& angles)
		{
			eulerAngles = angles;
		}

		void SetSpeed(float a_speed)
		{
			speed = a_speed;
		}

		// members
		NiPoint3 eulerAngles{};  // 00
		float    speed{ 0.0f };  // 0C
	};
	static_assert(sizeof(MovementVector) == 0x10);
}
