#pragma once

#include "RE/H/hkQueue.h"
#include "RE/H/hkbEvent.h"

namespace RE
{
	class hkbSymbolIdMap;

	/// A queue for storing hkbEvents.
	///
	/// An hkbEventQueue stores events using the external IDs that result from the linking process.
	/// In order to make it easier for nodes to enqueue events during update(), the queue stores a map between
	/// the local behavior's event IDs and those of the external symbol table.  When not doing update(), the map
	/// is null so you have to make sure to map the event to an external before putting it on the queue.
	class hkbEventQueue
	{
	public:
		int32_t convert_id(int32_t id) const;

		hkbEventQueue() = default;

		HK_HEAP_REDEFINE_NEW_NOVIRTUAL(hkbEventQueue);

		// members
		hkQueue<hkbEvent> queue;                          // 00
		hkbSymbolIdMap*   eventIDMap{ nullptr };          // 18
		bool              internal_or_external{ false };  // 20
		uint8_t           pad21[7];                       // 21
	};
	static_assert(sizeof(hkbEventQueue) == 0x28);
}
