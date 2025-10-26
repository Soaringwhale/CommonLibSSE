#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkStringPtr.h"

namespace RE
{
	class hkbSymbolLinker
	{
	public:
		struct hkStringMapStub
		{
			char nameToIdMap[0x10];  // 20 - hkStringMap<int32_t>

			hkStringMapStub()
			{
				using func_t = hkStringMapStub*(hkStringMapStub*);
				REL::Relocation<func_t> func{ RELOCATION_ID(57281, 57751) };
				func(this);
			}
		};
		static_assert(sizeof(hkStringMapStub) == 0x10);

		// members
		hkArray<hkStringPtr> idToNameMap;  // 00
		uint64_t             unk10{ 0 };   // 10 -- mb hkarray
		uint32_t             unk18{ 0 };   // 18
		uint8_t              pad1C[4];     // 1C
		hkStringMapStub      nameToIdMap;  // 20 - hkStringMap<int32_t>
	};
	static_assert(sizeof(hkbSymbolLinker) == 0x30);
}
