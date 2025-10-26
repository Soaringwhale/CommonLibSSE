#pragma once

#include "RE/H/hkVector4.h"
#include "RE/H/hkbModifier.h"

namespace RE
{
	/// A modifier that rotates the character worldFromModel in response to events.
	class hkbRotateCharacterModifier : public hkbModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbRotateCharacterModifier;
		inline static constexpr auto VTABLE = VTABLE_hkbRotateCharacterModifier;

		// members
		float     degreesPerSecond{ 90.0f };                     // 50 - The speed of rotation.
		float     speedMultiplier{ 1.0f };                       // 54 - The speed of rotation multiplier.
		uint8_t   pad88[8];                                      // 58
		hkVector4 axisOfRotation{ { 1.0f, 0.0f, 0.0f, 0.0f } };  // 60 - The axis of rotation.
		float     angle{ 0 };                                    // 70
		uint8_t   pad74[12];                                     // 74
	};
	static_assert(sizeof(hkbRotateCharacterModifier) == 0x80);
}
