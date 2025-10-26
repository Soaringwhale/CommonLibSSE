#pragma once

#include "RE/H/hkbEventBase.h"
#include "RE/H/hkbModifier.h"

namespace RE
{
	class BSEventOnFalseToTrueModifier : public hkbModifier
	{
		static constexpr inline size_t HANDLERS = 3;

	public:
		inline static constexpr auto RTTI = RTTI_BSEventOnFalseToTrueModifier;
		inline static constexpr auto VTABLE = VTABLE_BSEventOnFalseToTrueModifier;

		struct HandlerData
		{
			// members
			bool         bEnableEvent;     // 00
			bool         bVariableToTest;  // 01
			char         pad02[6];         // 02
			hkbEventBase event;            // 08
		};
		static_assert(sizeof(HandlerData) == 0x18);

		// members
		HandlerData datas[HANDLERS];                    // 58
		bool        bSlotActivatedLastFrame[HANDLERS];  // 98
		char        pad9B[5];                           // 9B
	};
	static_assert(sizeof(BSEventOnFalseToTrueModifier) == 0xA0);
}
