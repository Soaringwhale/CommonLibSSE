#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkQuaternion.h"
#include "RE/H/hkVector4.h"
#include "RE/H/hkbEvent.h"
#include "RE/H/hkbFootIkGains.h"
#include "RE/H/hkbModifier.h"

namespace RE
{
	/// The controls that influence the behavior of an hkbFootIkModifier.
	struct hkbFootIkControlData
	{
		// members
		hkbFootIkGains gains;  // 00 - foot Ik gains.
	};
	static_assert(sizeof(hkbFootIkControlData) == 0x30);

	/// Places foot IK control data into the track data to be blended in a behavior graph.
	///
	/// The control data is consumed by the hkbFootIkModifier, which should be placed
	/// rootward of this node in the behavior graph.
	class hkbFootIkControlsModifier : public hkbModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbFootIkControlsModifier;
		inline static constexpr auto VTABLE = VTABLE_hkbFootIkControlsModifier;

		/// The structure holds the output information for each leg.
		struct Leg
		{
			// members
			hkVector4        groundPosition;   // 00 - The position of the ground below the foot, as computed by the foot IK raycasts.
			hkbEventProperty ungroundedEvent;  // 10 - This event is sent if the foot raycast does not find a hit when the foot is supposed to be planted.
			float            verticalError;    // 20 - The distance between the input foot height and the ground.
			bool             hitSomething;     // 24 - Whether or not the ground was hit by the raycast.
			bool             isPlantedMS;      // 25 - Whether or not the foot is planted in model space in the incoming animation. If the height of the ankle goes below m_footPlantedAnkleHeightMS the foot is considered planted.
			uint8_t          pad26[10];        // 26
		};
		static_assert(sizeof(Leg) == 0x30);

		// members
		hkbFootIkControlData controlData;              // 50 - The control data for an hkbFootIkModifier.
		hkArray<Leg>         legs;                     // 80 - The output properties of each leg of the character.
		hkVector4            errorOutTranslation;      // 90
		hkQuaternion         alignWithGroundRotation;  // A0
	};
	static_assert(sizeof(hkbFootIkControlsModifier) == 0xB0);
}
