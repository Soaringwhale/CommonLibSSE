#include "RE/H/hkbSymbolIdMap.h"

namespace RE
{
	int32_t hkbSymbolIdMap::getExternal(int32_t internal) const
	{
		return ((internal < 0) ? internal : internalToExternalMap[internal]);
	}

	int32_t hkbSymbolIdMap::getInternal(int32_t external) const
	{
		return ((external < 0) ? external : externalToInternalMap.getWithDefault(external, -1));
	}
}
