#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkQsTransform.h"
#include "RE/H/hkbGenerator.h"

namespace RE
{
	class BSOffsetAnimationGenerator : public hkbGenerator
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSOffsetAnimationGenerator;
		inline static constexpr auto VTABLE = VTABLE_BSOffsetAnimationGenerator;

		// members
		uint8_t                pad48[8];              // 48
		hkbGenerator*          pDefaultGenerator;     // 50
		uint8_t                pad58[8];              // 58
		hkbClipGenerator*      pOffsetClipGenerator;  // 60
		float                  fOffsetVariable;       // 68
		float                  fOffsetRangeStart;     // 6C
		float                  fOffsetRangeEnd;       // 70
		uint8_t                pad74[4];              // 74
		hkArray<hkQsTransform> BoneOffsetA;           // 78
		hkArray<int16_t>       BoneIndexA;            // 88
		float                  fCurrentPercentage;    // 98
		uint32_t               iCurrentFrame;         // 9C
		bool                   bZeroOffset;           // A0
		bool                   bOffsetValid;          // A1
		uint8_t                padA2[14];             // 78
	};
	static_assert(sizeof(BSOffsetAnimationGenerator) == 0xB0);
}
