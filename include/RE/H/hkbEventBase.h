#pragma once

#include "RE/H/hkRefPtr.h"
#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkbEventPayload;

	class hkbEventBase
	{
	public:
		enum SystemEventIDs_ : int32_t
		{
			kNull = static_cast<std::underlying_type_t<SystemEventIDs_>>(-1)
		};

		// members
		int32_t          id{ kNull };  // 00
		uint32_t         pad04;        // 04
		hkbEventPayload* payload;      // 08
	};
	static_assert(sizeof(hkbEventBase) == 0x10);
}
