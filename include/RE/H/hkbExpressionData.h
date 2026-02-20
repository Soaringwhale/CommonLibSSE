#pragma once

#include "RE/H/hkStringPtr.h"

namespace RE
{
	/// An expression and its event mode.
	struct hkbExpressionData
	{
		/// The modes for sending events based on the expression.
		enum class ExpressionEventMode : uint8_t
		{
			/// Send the event once the first time that the expression is true.
			EVENT_MODE_SEND_ONCE = 0x0,

			/// Send the event every frame if the expression is true.
			EVENT_MODE_SEND_ON_TRUE = 0x1,

			/// Send the event every frame in which the expression becomes true after having been false on the previous frame.
			EVENT_MODE_SEND_ON_FALSE_TO_TRUE = 0x2,

			/// Send the event every frame after it first becomes true.
			EVENT_MODE_SEND_EVERY_FRAME_ONCE_TRUE = 0x3,
		};

		// members
		hkStringPtr         expression;               // 00 - "variablename = expression" or "eventname = boolean expression"
		int32_t             assignmentVariableIndex;  // 08 - This is the variable that we will assign result to (-1 if not found)
		int32_t             assignmentEventIndex;     // 0C - This is the event we will raise if result > 0 (-1 if not found)
		ExpressionEventMode eventMode;                // 10 - Under what circumstances to send the event.
		bool                raisedEvent;              // 11 - Whether the event has been sent yet.
		bool                wasTrueInPreviousFrame;   // 12 - Whether the expression was true in the previous frame.
		char                pad13[5];                 // 13
	};
	static_assert(sizeof(hkbExpressionData) == 0x18);
}
