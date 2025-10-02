#pragma once

#include "RE/H/hkQsTransform.h"
#include "RE/H/hkbGenerator.h"

namespace RE
{
	class hkbClipGenerator;

	class BSSynchronizedClipGenerator : public hkbGenerator
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSSynchronizedClipGenerator;
		inline static constexpr auto VTABLE = VTABLE_BSSynchronizedClipGenerator;

		// members
		uint8_t           pad48[8];                      // 048
		hkbClipGenerator* pClipGenerator;                // 050
		const char*       SyncAnimPrefix;                // 058
		bool              bSyncClipIgnoreMarkPlacement;  // 060
		uint8_t           pad61[3];                      // 061
		float             fGetToMarkTime;                // 064
		float             fMarkErrorThreshold;           // 068
		bool              bLeadCharacter;                // 06C
		bool              bReorientSupportChar;          // 06D
		bool              bApplyMotionFromRoot;          // 06E
		uint8_t           pad_6F;                        // 06F
		void*             pSyncScene;                    // 070
		uint8_t           pad78[8];                      // 078
		hkQsTransform     StartMarkWS;                   // 080
		hkQsTransform     EndMarkWS;                     // 0B0
		hkQsTransform     StartMarkMS;                   // 0E0
		float             fCurrentLerp;                  // 110
		uint8_t           pad_114[4];                    // 114
		void*             pLocalSyncBinding;             // 118
		void*             pEventMap;                     // 120
		int16_t           sAnimationBindingIndex;        // 128
		bool              bAtMark;                       // 12A
		bool              bAllCharactersInScene;         // 12B
		bool              bAllCharactersAtMarks;         // 12C
		uint8_t           pad12D[3];                     // 12D
	};
	static_assert(sizeof(BSSynchronizedClipGenerator) == 0x130);

}
