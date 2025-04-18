#include "RE/H/hkbEventQueue.h"

#include "RE/H/hkbSymbolIdMap.h"

namespace RE
{
	int32_t hkbEventQueue::convert_id(int32_t id) const
	{
		if (!eventIDMap)
			return id;

		if (internal_or_external) {
			id = eventIDMap->getExternal(id);
		} else {
			id = eventIDMap->getInternal(id);
		}

		return id;
	}
}
