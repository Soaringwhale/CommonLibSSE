#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkVector4.h"
#include "RE/H/hkbCharacterControllerSetup.h"

namespace RE
{
	class hkbCharacterStringData;
	class hkbFootIkDriverInfo;
	class hkbHandIkDriverInfo;
	class hkbMirroredSkeletonInfo;
	class hkbVariableInfo;
	class hkbVariableValueSet;

	class hkbCharacterData : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbCharacterData;
		inline static constexpr auto VTABLE = VTABLE_hkbCharacterData;

		static const hkClass& staticClass()
		{
			return *REL::Relocation<hkClass*>(REL::ID(521060));
		}

		// members
		hkbCharacterControllerSetup       characterControllerSetup;  // 10 (hkbCharacterControllerSetup)
		hkVector4                         modelUpMS;                 // 30
		hkVector4                         modelForwardMS;            // 40
		hkVector4                         modelRightMS;              // 50
		hkArray<hkbVariableInfo>          characterPropertyInfos;    // 60
		hkArray<std::int32_t>             numBonesPerLod;            // 70
		hkRefPtr<hkbVariableValueSet>     characterPropertyValues;   // 80
		hkRefPtr<hkbFootIkDriverInfo>     footIkDriverInfo;          // 88
		hkRefPtr<hkbHandIkDriverInfo>     handIkDriverInfo;          // 90
		hkRefPtr<hkbCharacterStringData>  stringData;                // 98
		hkRefPtr<hkbMirroredSkeletonInfo> mirroredSkeletonInfo;      // A0
		float                             scale;                     // A8
		uint16_t                          mb_numHands;               // AC
		uint16_t                          mb_numFloatSlots;          // AE
	};
	static_assert(sizeof(hkbCharacterData) == 0xB0);
}
