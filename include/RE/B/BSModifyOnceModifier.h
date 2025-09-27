#pragma once

#include "RE/H/hkbModifier.h"

namespace RE
{
	class BSModifyOnceModifier : public hkbModifier
	{
	public:
		// members
		hkRefPtr<hkbModifier> pOnActivateModifier;    // 50
		uint8_t               pad58[8];               // 58
		hkRefPtr<hkbModifier> pOnDeactivateModifier;  // 60
		uint8_t               pad68[8];               // 68
	};
	static_assert(sizeof(BSModifyOnceModifier) == 0x70);
}
