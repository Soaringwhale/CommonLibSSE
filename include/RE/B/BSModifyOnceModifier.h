#pragma once

#include "RE/H/hkbModifier.h"

namespace RE
{
	class BSModifyOnceModifier : public hkbModifier
	{
	public:
		// members
		hkRefPtr<hkbModifier> pOnActivateModifier;    // 50
		uint64_t              unk58;                  // 58
		hkRefPtr<hkbModifier> pOnDeactivateModifier;  // 60
	};
	static_assert(sizeof(BSModifyOnceModifier) == 0x68);
}
