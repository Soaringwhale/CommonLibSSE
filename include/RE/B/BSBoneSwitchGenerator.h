#pragma once

#include "RE/H/hkbGenerator.h"

namespace RE
{
	class BSBoneSwitchGeneratorBoneData;

	class BSBoneSwitchGenerator : public hkbGenerator
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSBoneSwitchGenerator;
		inline static constexpr auto VTABLE = VTABLE_BSBoneSwitchGenerator;

		// members
		uint8_t                                 pad48[8];           // 48
		hkbGenerator*                           pDefaultGenerator;  // 50
		hkArray<BSBoneSwitchGeneratorBoneData*> ChildrenA;          // 58
		uint8_t                                 pad68[8];           // 68
	};
	static_assert(sizeof(BSBoneSwitchGenerator) == 0x70);
}
