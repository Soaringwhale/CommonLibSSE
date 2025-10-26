#pragma once

#include "RE/H/hkbModifier.h"

namespace RE
{
	/// Applies a sequence of modifiers as a single modifier.
	///
	/// This class is especially useful if a behavior graph shares a sequence of
	/// modifiers among several branches.  You can create the sequence once and then
	/// just add it to each branch instead of having to add all of the modifiers
	/// individually.
	class hkbModifierList : public hkbModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbModifierList;
		inline static constexpr auto VTABLE = VTABLE_hkbModifierList;

		// members
		hkArray<hkbModifier*> modifiers;  // 50 - The list of modifiers to apply.
	};
	static_assert(sizeof(hkbModifierList) == 0x60);
}
