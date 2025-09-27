#pragma once

#include "RE/H/hkbEvent.h"
#include "RE/H/hkbModifier.h"

namespace RE
{
	class BSEventOnDeactivateModifier : public hkbModifier
	{
	public:
		// members
		hkbEventProperty event;  // 50
	};
	static_assert(sizeof(BSEventOnDeactivateModifier) == 0x60);
}
