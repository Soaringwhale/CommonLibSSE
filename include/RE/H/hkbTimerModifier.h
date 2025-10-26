#pragma once

#include "RE/H/hkbEventBase.h"
#include "RE/H/hkbModifier.h"

namespace RE
{
	/// A modifier for sending an event after a time lapse.
	class hkbTimerModifier : public hkbModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbTimerModifier;
		inline static constexpr auto VTABLE = VTABLE_hkbTimerModifier;

		hkbTimerModifier() { stl::emplace_vtable(this); }

		// members
		float            alarmTimeSeconds;  // 50 - When the timer alarm goes off.
		uint8_t          pad54[4];          // 54
		hkbEventProperty alarmEvent;        // 58 - The event id to send when the alarm goes off.
		float            secondsElapsed;    // 68
		uint8_t          pad6C[4];          // 6C
	};
	static_assert(sizeof(hkbTimerModifier) == 0x70);
}
