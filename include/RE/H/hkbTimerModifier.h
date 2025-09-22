#pragma once

#include "RE/H/hkbEventBase.h"
#include "RE/H/hkbModifier.h"

namespace RE
{
	class hkbTimerModifier : public hkbModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbTimerModifier;
		inline static constexpr auto VTABLE = VTABLE_hkbTimerModifier;

		hkbTimerModifier() { stl::emplace_vtable(this); }

		// members
		float        alarmTimeSeconds;  // 50
		uint8_t      pad54[4];          // 54
		hkbEventBase alarmEvent;        // 58
		float        secondsElapsed;    // 68
		uint8_t      pad6C[4];          // 6C
	};
	static_assert(sizeof(hkbTimerModifier) == 0x70);
}
