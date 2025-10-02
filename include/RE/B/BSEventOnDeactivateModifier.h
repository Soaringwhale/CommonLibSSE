#pragma once

#include "RE/H/hkbEvent.h"
#include "RE/H/hkbModifier.h"

namespace RE
{
	class BSEventOnDeactivateModifier : public hkbModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSEventOnDeactivateModifier;
		inline static constexpr auto VTABLE = VTABLE_BSEventOnDeactivateModifier;

		// members
		hkbEventProperty event;  // 50
	};
	static_assert(sizeof(BSEventOnDeactivateModifier) == 0x60);
}
