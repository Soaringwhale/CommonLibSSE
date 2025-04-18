#pragma once

#include "RE/H/hkbModifier.h"

namespace RE
{
	class BSIsActiveModifier : public hkbModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSIsActiveModifier;
		inline static constexpr auto VTABLE = VTABLE_BSIsActiveModifier;

		BSIsActiveModifier() { stl::emplace_vtable(this); }

		// members
		bool bIsActive0;      // 50
		bool bInvertActive0;  // 51
		bool bIsActive1;      // 52
		bool bInvertActive1;  // 53
		bool bIsActive2;      // 54
		bool bInvertActive2;  // 55
		bool bIsActive3;      // 56
		bool bInvertActive3;  // 57
		bool bIsActive4;      // 58
		bool bInvertActive4;  // 59
		char pad5A[6];        // 5A
	};
	static_assert(sizeof(BSIsActiveModifier) == 0x60);
}
