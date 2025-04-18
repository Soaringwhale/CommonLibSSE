#pragma once

#include "RE/H/hkbGenerator.h"

namespace RE
{
	class hkbGenerator;
	class hkbModifier;

	class hkbModifierGenerator : public hkbGenerator
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbModifierGenerator;
		inline static constexpr auto VTABLE = VTABLE_hkbModifierGenerator;

		static const hkClass& staticClass()
		{
			return *REL::Relocation<hkClass*>(REL::ID(521260));
		}

		hkbModifierGenerator() { stl::emplace_vtable(this); }
		hkbModifierGenerator(hkbModifier* modifier, hkbGenerator* generator);
		~hkbModifierGenerator() override = default;  // 00

		// override (hkReferencedObject)
		const hkClass* GetClassType() const override { return &staticClass(); }  // 01

		// override (hkbNode)
		void     getChildren(GET_CHILDREN_FLAGS flags, ChildrenInfo& ans) override;  // 09
		bool     isValid(hkStringPtr&) const override { return generator.get(); }    // 0A
		hkbNode* cloneNode(hkbBehaviorGraph& rootBehavior) const override;           // 0C

		// override (hkbGenerator)
		void generate(const hkbContext& a_context, const hkbGeneratorOutput** activeChildrenOutput, hkbGeneratorOutput& output, float timeOffset = 0.0f) const override;  // 17
		bool canRecycleOutput() const override { return true; }                                                                                                           // 18
		void updateSync(const hkbContext& a_context, hkbNodeInfo& info) override;                                                                                         // 19

		// members
		hkRefPtr<hkbModifier>  modifier;   // 48
		hkRefPtr<hkbGenerator> generator;  // 50

	private:
		hkbModifierGenerator(const hkbModifierGenerator& other);
	};
	static_assert(sizeof(hkbModifierGenerator) == 0x58);
}
