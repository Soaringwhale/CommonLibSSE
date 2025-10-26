#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkaSkeleton.h"
#include "RE/H/hkaSkeletonMapper.h"
#include "RE/H/hkbAnimationBindingSet.h"
#include "RE/H/hkbCharacterData.h"
#include "RE/H/hkbSymbolIdMap.h"

namespace RE
{
	class hkaMirroredSkeleton;
	class hkaSkeleton;
	class hkCriticalSection;

	class hkbCharacterSetup : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbCharacterSetup;
		inline static constexpr auto VTABLE = VTABLE_hkbCharacterSetup;

		hkbCharacterSetup()
		{
			stl::emplace_vtable(this);
		}

		// members
		hkArray<hkRefPtr<hkaSkeletonMapper>> retargetingSkeletonMappers;        // 10 - Array of skeleton mappers for animation retargeting.
		hkRefPtr<hkaSkeleton>                animationSkeleton;                 // 20 - The animation skeleton. For the scaled character the reference pose inside this skeleton is scaled.
		hkRefPtr<hkaSkeletonMapper>          ragdollToAnimationSkeletonMapper;  // 28 - A mapper from the ragdoll skeleton to the animation skeleton.
		hkRefPtr<hkaSkeletonMapper>          animationToRagdollSkeletonMapper;  // 30 - A mapper from the animation skeleton to the ragdoll skeleton.
		hkRefPtr<hkbAnimationBindingSet>     animationBindingSet;               // 38 - The animation bindings used for this character.  These get hooked up based on the data in hkbCharacterStringData::m_animationBundleNameData and hkbCharacterStringData::m_animationBundleFilenameData.
		hkRefPtr<hkbCharacterData>           data;                              // 40 - Serialized data for the character.
		hkRefPtr<hkaSkeleton>                unscaledAnimationSkeleton;         // 48 - The animation skeleton. If the character is scaled then this points to the unscaled version of the skeleton. If character is not scaled then this is null.
		hkRefPtr<hkbSymbolIdMap>             characterPropertyIdMap;            // 50 - An ID mapper from internal character property IDs to external IDs.
	};
	static_assert(sizeof(hkbCharacterSetup) == 0x58);
}
