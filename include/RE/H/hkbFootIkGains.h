#pragma once

namespace RE
{
	/// These gains control how much smoothing occurs in the foot IK process.
	struct hkbFootIkGains
	{
	public:
		// members
		float onOffGain;                   // 00
		float groundAscendingGain;         // 04
		float groundDescendingGain;        // 08
		float footPlantedGain;             // 0C
		float footRaisedGain;              // 10
		float footUnlockGain;              // 14
		float worldFromModelFeedbackGain;  // 18
		float errorUpDownBias;             // 1C
		float alignWorldFromModelGain;     // 20
		float hipOrientationGain;          // 24
		float maxKneeAngleDifference;      // 28
		float ankleOrientationGain;        // 2C
	};
	static_assert(sizeof(hkbFootIkGains) == 0x30);
}
