#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkMap.h"
#include "RE/H/hkReferencedObject.h"

namespace RE
{
	/// A map of symbol IDs.
	///
	/// Some objects like hkbBehaviorGraph and hkbSequence can contain their own indexed lists
	/// of symbols such as event names, variable names, etc.  An hkbSymbolIdMap maintains
	/// a map from the local IDs of such an object, and the IDs in a global list or in
	/// another object.
	class hkbSymbolIdMap : public hkReferencedObject
	{
	public:
		/// Map an internal ID to an external ID.
		int32_t getExternal(int32_t internal) const;

		/// Map an external ID to an internal ID.
		int32_t getInternal(int32_t external) const;

		// members

		/// 10 - The map from internal IDs to external IDs.
		///
		/// The internal symbols are typically indexed sequentially starting
		/// at 0, so we use a dense array to store the map.
		hkArray<int32_t> internalToExternalMap;

		/// 20 - The map from external IDs to internal UDs.
		///
		/// Typically, only a subset of the external symbol IDs are covered
		/// by the internal IDs, so we use a sparse map representation.
		hkPointerMap<int32_t, int32_t> externalToInternalMap;
	};
	static_assert(sizeof(hkbSymbolIdMap) == 0x30);
}
