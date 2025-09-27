#pragma once

#include "RE/H/hkbModifierWrapper.h"

namespace RE
{
	class hkbEventDrivenModifier : public hkbModifierWrapper
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbEventDrivenModifier;
		inline static constexpr auto VTABLE = VTABLE_hkbEventDrivenModifier;

		// members
		int32_t activateEventId;    // 58 - Event used to activate the wrapped modifier
		int32_t deactivateEventId;  // 5C - Event used to deactivate the wrapped modifier
		bool    activeByDefault;    // 60 - If the child needs to be activated when this modifier is activated set this to true.
		bool    isActive;           // 61
		char    pad62[6];           // 62
	};
	static_assert(sizeof(hkbEventDrivenModifier) == 0x68);
}
