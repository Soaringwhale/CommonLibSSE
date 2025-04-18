#pragma once

#include "RE/H/hkbGenerator.h"
#include "RE/H/hkbEventBase.h"

namespace RE
{
	class BGSGamebryoSequenceTrigger
	{
	public:
		// members
		float        time1;  // 00
		float        time2;  // 04
		hkbEventBase event;  // 08
	};
	static_assert(sizeof(BGSGamebryoSequenceTrigger) == 0x18);

	class BGSGamebryoSequenceGenerator : public hkbGenerator
	{
	public:
		// members
		char*                               pSequence;           // 48
		uint8_t                             eBlendModeFunction;  // 50
		char                                pad51[3];            // 51
		float                               fPercent;            // 54
		hkArray<BGSGamebryoSequenceTrigger> events;              // 58
		float                               fTime;               // 68
		bool                                bDelayedActivate;    // 6C
		bool                                bLooping;            // 6D
		char                                pad6E[2];            // 6E
	};
	static_assert(sizeof(BGSGamebryoSequenceGenerator) == 0x70);
}
