#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkbEvent.h"
#include "RE/H/hkbModifier.h"

namespace RE
{
	/// A range, an event and the event mode.
	struct hkbEventRangeData
	{
		enum class EventRangeMode : uint8_t
		{
			/// Send the event every frame in which the range is entered after having
			/// been outside the range on the previous frame.
			EVENT_MODE_SEND_ON_ENTER_RANGE,

			/// Send the event every frame if the value is in the range.
			EVENT_MODE_SEND_WHEN_IN_RANGE
		};

		// members
		float            upperBound;  // 00 - The highest value in this range.  The lowest value of this range is the upperBound from the previous range.
		uint8_t          pad04[4];    // 04
		hkbEventProperty event;       // 08
		EventRangeMode   eventMode;   // 18 - Under what circumstances to send the event.
		uint8_t          pad19[7];    // 19
	};
	static_assert(sizeof(hkbEventRangeData) == 0x20);

	/// An array of expressions wrapped for shared access.
	class hkbEventRangeDataArray : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbEventRangeDataArray;
		inline static constexpr auto VTABLE = VTABLE_hkbEventRangeDataArray;

		// members
		hkArray<hkbEventRangeData> eventData;  // 10 - A series of intervals, each of which has an event associated with it. Note that these must be in increasing order.
	};
	static_assert(sizeof(hkbEventRangeDataArray) == 0x20);

	class hkbEventsFromRangeModifier : public hkbModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbEventsFromRangeModifier;
		inline static constexpr auto VTABLE = VTABLE_hkbEventsFromRangeModifier;

		// members
		float                            inputValue;                // 50 - The value that is checked against the ranges to decide which events should be sent.
		float                            lowerBound;                // 54 - A lower bound of all of the range intervals.
		hkRefPtr<hkbEventRangeDataArray> eventRanges;               // 58 - A series of intervals, each of which has an event associated with it. Note that these must be in increasing order.
		hkArray<bool>                    wasActiveInPreviousFrame;  // 60 - Was the range active in the previous frame.
	};
	static_assert(sizeof(hkbEventsFromRangeModifier) == 0x70);
}
