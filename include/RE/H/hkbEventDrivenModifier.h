#pragma once

#include "RE/H/hkbModifierWrapper.h"

namespace RE
{
	class hkbEventDrivenModifier : public hkbModifierWrapper
	{
	public:
		// members
		int32_t activateEventId;    // 58
		int32_t deactivateEventId;  // 5C
		bool    activeByDefault;    // 60
		bool    isActive;           // 61
		char    pad62[6];           // 62
	};
	static_assert(sizeof(hkbEventDrivenModifier) == 0x68);
}
