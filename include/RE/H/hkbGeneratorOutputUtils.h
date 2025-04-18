#pragma once

namespace RE
{
	struct hkbGeneratorOutput;

	namespace hkbGeneratorOutputUtils
	{
		/// Copy outputIn into outputOut.
		void copyGeneratorOutput(const hkbGeneratorOutput& from, hkbGeneratorOutput& to);
		/// Copy only valid track data in outputFrom to outputTo, optionally you can ignore coping pose track.
		void copyTrackData(const hkbGeneratorOutput& from, hkbGeneratorOutput& to, bool copyPoseTrack = true);
	}
}
