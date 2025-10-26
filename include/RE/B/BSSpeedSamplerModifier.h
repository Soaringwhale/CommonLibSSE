#pragma once

#include "RE/H/hkbModifier.h"

namespace RE
{
	class BSSpeedSamplerModifier : public hkbModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSSpeedSamplerModifier;
		inline static constexpr auto VTABLE = VTABLE_BSSpeedSamplerModifier;

		BSSpeedSamplerModifier() { stl::emplace_vtable(this); }

		// members
		int32_t state{ -1 };     // 50
		float   direction{ 0 };  // 54
		float   goalSpeed{ 0 };  // 58
		float   speedOut{ 0 };   // 5C
	};
	static_assert(sizeof(BSSpeedSamplerModifier) == 0x60);
}
