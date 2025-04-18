#pragma once

#include "RE/H/hkbModifier.h"

namespace RE
{
	class hkbModifierWrapper : public hkbModifier
	{
	public:
		// members
		hkRefPtr<hkbModifier> modifier;  // 50
	};
	static_assert(sizeof(hkbModifierWrapper) == 0x58);
}
