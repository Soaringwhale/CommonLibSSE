#include "RE/H/hkbGeneratorOutputUtils.h"

namespace RE
{
	void hkbGeneratorOutputUtils::copyGeneratorOutput(const hkbGeneratorOutput& from, hkbGeneratorOutput& to)
	{
		copyTrackData(from, to);
	}

	void hkbGeneratorOutputUtils::copyTrackData(const hkbGeneratorOutput& from, hkbGeneratorOutput& to, bool copyPoseTrack)
	{
		using func_t = decltype(&hkbGeneratorOutputUtils::copyTrackData);
		REL::Relocation<func_t> func{ RELOCATION_ID(58633, 0) };
		return func(from, to, copyPoseTrack);
	}
}
