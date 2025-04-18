#pragma once

#include "RE/H/hkRefPtr.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkVector4.h"
#include "RE/H/hkbTransitionEffect.h"

namespace RE
{
	class hkbProjectStringData;

	class hkbProjectData : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbProjectData;
		inline static constexpr auto VTABLE = VTABLE_hkbProjectData;

		static const hkClass& staticClass()
		{
			return *REL::Relocation<hkClass*>(REL::ID(521732));
		}

		// members
		hkVector4                      worldUpWS;         // 10
		hkRefPtr<hkbProjectStringData> stringData;        // 20
		hkbTransitionEffect::EventMode defaultEventMode;  // 28
	};
	static_assert(sizeof(hkbProjectData) == 0x30);
}
