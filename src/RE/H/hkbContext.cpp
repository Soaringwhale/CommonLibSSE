#include "RE/H/hkbContext.h"

namespace RE
{
	hkbEventQueue* hkbContext::getEventQueue() const
	{
		if (eventQueue) {
			return eventQueue;
		} else {
			return character->getEventQueue();
		}
	}
}
