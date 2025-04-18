#include "RE/H/hkbTransitionEffect.h"

namespace RE
{
	bool hkbTransitionEffect::computeSelfTransitionMode(const hkbContext& ctx, hkbGenerator* gen)
	{
		using func_t = decltype(&hkbTransitionEffect::computeSelfTransitionMode);
		REL::Relocation<func_t> func{ RELOCATION_ID(58829, 0) };
		return func(this, ctx, gen);
	}

	hkbTransitionEffect::EventMode hkbTransitionEffect::getEventMode() const
	{
		if (eventMode != EventMode::EVENT_MODE_DEFAULT)
			return eventMode;
		else
			return defaultEventMode;
	}
}
