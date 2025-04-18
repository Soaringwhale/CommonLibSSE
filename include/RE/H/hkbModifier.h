#pragma once

#include "RE/H/hkbNode.h"

namespace RE
{
	class hkClass;
	struct hkbGeneratorOutput;
	class hkbGeneratorSyncInfo;

	class hkbModifier : public hkbNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbModifier;
		inline static constexpr auto VTABLE = VTABLE_hkbModifier;

		static const hkClass& staticClass()
		{
			return *REL::Relocation<hkClass*>(REL::ID(521711));
		}

		hkbModifier() { stl::emplace_vtable(this); }
		~hkbModifier() override = default;  // 00

		//add
		void modify([[maybe_unused]] const hkbContext& ctx, [[maybe_unused]] hkbGeneratorOutput& ans) { userData |= 2; }  // 17
		void modifySyncInfo([[maybe_unused]] const hkbContext& ctx, [[maybe_unused]] hkbGeneratorSyncInfo& info) {}       // 18

		// members
		bool enable{ true };  // 48
		char pad49[7];        // 49
	};
	static_assert(sizeof(hkbModifier) == 0x50);

	class BSTweenerModifier : public hkbModifier
	{
	public:
		// TODO

		static const hkClass& staticClass()
		{
			return *REL::Relocation<hkClass*>(REL::ID(522966));
		}
	};
}
