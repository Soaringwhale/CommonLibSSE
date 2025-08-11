#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkRefPtr.h"

namespace RE
{
	class hkaAnimation;
	class hkaAnimationBinding;
	class hkaBoneAttachment;
	class hkaMeshBinding;
	class hkaSkeleton;

	class hkaAnimationContainer : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkReferencedObject;
		inline static constexpr auto VTABLE = VTABLE_hkReferencedObject;

		~hkaAnimationContainer() override;  // 00

		// members
		hkArray<hkRefPtr<hkaSkeleton>>         skeletons;    // 10
		hkArray<hkRefPtr<hkaAnimation>>        animations;   // 20
		hkArray<hkRefPtr<hkaAnimationBinding>> bindings;     // 30
		hkArray<hkRefPtr<hkaBoneAttachment>>   attachments;  // 40
		hkArray<hkRefPtr<hkaMeshBinding>>      skins;        // 50
	};
	static_assert(sizeof(hkaAnimationContainer) == 0x60);
}
