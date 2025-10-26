#pragma once

#include "RE/H/hkbEvent.h"
#include "RE/H/hkbModifier.h"

namespace RE
{
	class BSEventEveryNEventsModifier : public hkbModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSEventEveryNEventsModifier;
		inline static constexpr auto VTABLE = VTABLE_BSEventEveryNEventsModifier;

		// members
		hkbEventProperty eventToCheckFor;                       // 50
		hkbEventProperty eventToSend;                           // 60
		int8_t           numberOfEventsBeforeSend{ 1 };         // 70
		int8_t           minimumNumberOfEventsBeforeSend{ 1 };  // 71
		bool             randomizeNumberOfEvents{ 0 };          // 72
		uint8_t          pad73[1];                              // 73
		int32_t          numberOfEventsSeen;                    // 74
		int8_t           calculatedNumberOfEventsBeforeSend;    // 78
		uint8_t          pad79[7];                              // 79
	};
	static_assert(sizeof(BSEventEveryNEventsModifier) == 0x80);
}
