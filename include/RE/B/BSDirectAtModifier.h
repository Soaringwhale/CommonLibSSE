#pragma once

#include "RE/H/hkVector4.h"
#include "RE/H/hkbModifier.h"

namespace RE
{
	class BSDirectAtModifier : public hkbModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSDirectAtModifier;
		inline static constexpr auto VTABLE = VTABLE_BSDirectAtModifier;

		// members
		bool             directAtTarget{ true };                        // 50
		uint8_t          pad81[1];                                      // 51
		int16_t          sourceBoneIndex{ -1 };                         // 52
		int16_t          startBoneIndex{ -1 };                          // 54
		int16_t          endBoneIndex{ -1 };                            // 56
		float            limitHeadingDegrees{ 90.0f };                  // 58
		float            limitPitchDegrees{ 90.0f };                    // 5C
		float            offsetHeadingDegrees{ 0 };                     // 60
		float            offsetPitchDegrees{ 0 };                       // 64
		float            onGain{ 0.05f };                               // 68
		float            offGain{ 0.05f };                              // 6C
		hkVector4        targetLocation{ { 0.0f, 0.0f, 0.0f, 0.0f } };  // 70
		uint32_t         userInfo{ 0 };                                 // 80
		bool             directAtCamera{ 0 };                           // 84
		uint8_t          pad133[3];                                     // 85
		float            directAtCameraX{ 0 };                          // 88
		float            directAtCameraY{ 0 };                          // 8C
		float            directAtCameraZ{ 0 };                          // 90
		bool             active{ 0 };                                   // 94
		uint8_t          pad149[3];                                     // 95
		float            currentHeadingOffset{ 0 };                     // 98
		float            currentPitchOffset{ 0 };                       // 9C
		float            timeStep;                                      // A0
		uint8_t          pad164[4];                                     // a4
		void*            pSkeletonMemory;                               // A8
		bool             hasTarget;                                     // B0
		uint8_t          pad177[15];                                    // b1
		hkVector4        directAtTargetLocation;                        // C0
		hkArray<int16_t> boneChainIndices;                              // D0
	};
	static_assert(sizeof(BSDirectAtModifier) == 0xE0);
}
