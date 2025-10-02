#pragma once

#include "RE/H/hkbEventBase.h"
#include "RE/H/hkbGenerator.h"

namespace RE
{
	class hkbBlenderGenerator;
	class hkbBlendingTransitionEffect;

	class BSCyclicBlendTransitionGenerator : public hkbGenerator
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSCyclicBlendTransitionGenerator;
		inline static constexpr auto VTABLE = VTABLE_BSCyclicBlendTransitionGenerator;

		enum class CurrentBlendMode : int8_t
		{
			MODE_INACTIVE = -1,
			MODE_DEFAULT = 0x0,
			MODE_FROZEN = 0x1,
			MODE_BLENDING = 0x2,
			MODE_WAITINGFORBLENDING = 0x3,
		};

		// members
		uint8_t                      pad48[8];                     // 48
		hkbBlenderGenerator*         pBlenderGenerator;            // 50
		hkbEventBase                 EventToFreezeBlendValue;      // 58
		hkbEventBase                 EventToCrossBlend;            // 68
		float                        fBlendParameter;              // 78
		float                        fTransitionDuration;          // 7C
		uint8_t                      eBlendCurve;                  // 80
		uint8_t                      pad81[15];                    // 81
		hkbBlenderGenerator*         pTransitionBlenderGenerator;  // 90
		uint8_t                      pad98[8];                     // 98
		hkbBlendingTransitionEffect* pTransitionEffect;            // A0
		CurrentBlendMode             currentMode;                  // A8
		uint8_t                      pad_A9[7];                    // A9
	};
	static_assert(sizeof(BSCyclicBlendTransitionGenerator) == 0xB0);
}
