#pragma once

#include "RE/H/hkbGenerator.h"

namespace RE
{
	class BSiStateTaggingGenerator : public hkbGenerator
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSiStateTaggingGenerator;
		inline static constexpr auto VTABLE = VTABLE_BSiStateTaggingGenerator;

		static const hkClass& staticClass()
		{
			return *REL::Relocation<hkClass*>(REL::ID(522820));
		}

		BSiStateTaggingGenerator() { stl::emplace_vtable(this); }
		BSiStateTaggingGenerator(uint32_t iState, uint32_t priority, hkbGenerator* generator) :
			iStateToSetAs(iState), iPriority(priority), pDefaultGenerator(generator) { stl::emplace_vtable(this); }
		~BSiStateTaggingGenerator() = default;

		// override (hkReferencedObject)
		const hkClass* GetClassType() const override { return &staticClass(); }  // 01

		// override (hkbNode)
		int32_t  getMaxNumChildren(GET_CHILDREN_FLAGS) override { return pDefaultGenerator != nullptr; }      // 08
		void     getChildren(GET_CHILDREN_FLAGS flags, ChildrenInfo& ans) override;                           // 09
		bool     isValid(hkStringPtr&) const override { return pDefaultGenerator != nullptr; }                // 0A
		hkbNode* cloneNode(hkbBehaviorGraph&) const override { return new BSiStateTaggingGenerator(*this); }  // 0C

		// override (hkbGenerator)
		void generate(const hkbContext& a_context, const hkbGeneratorOutput** activeChildrenOutput, hkbGeneratorOutput& output, float timeOffset = 0.0f) const override;  // 17
		bool canRecycleOutput() const override { return true; }                                                                                                           // 18
		void updateSync(const hkbContext& a_context, hkbNodeInfo& info) override;                                                                                         // 19

		// members
		uint64_t      field_48;                      // 48
		hkbGenerator* pDefaultGenerator{ nullptr };  // 50
		uint32_t      iStateToSetAs{ 0 };            // 54
		uint32_t      iPriority{ 0 };                // 58

	private:
		BSiStateTaggingGenerator(const BSiStateTaggingGenerator& other);
	};
	static_assert(sizeof(BSiStateTaggingGenerator) == 0x60);
}
