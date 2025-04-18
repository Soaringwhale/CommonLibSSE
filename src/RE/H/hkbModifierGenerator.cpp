#include "RE/H/hkbModifierGenerator.h"

#include "RE/H/hkbBehaviorGraph.h"
#include "RE/H/hkbModifier.h"
#include "RE/H/hkbModifierList.h"
#include "RE/H/hkbNodeInfo.h"
#include "RE/H/hkbUtils.h"

namespace RE
{
	hkbModifierGenerator::hkbModifierGenerator(hkbModifier* a_modifier, hkbGenerator* a_generator) :
		modifier(a_modifier), generator(a_generator)
	{
		stl::emplace_vtable(this);
	}

	void hkbModifierGenerator::getChildren(GET_CHILDREN_FLAGS flags, ChildrenInfo& ans)
	{
		bool activeOnly = flags.all(GET_CHILDREN_FLAG::kActiveOnly);
		bool modifierAdded = !flags.all(GET_CHILDREN_FLAG::kGeneratorsOnly) && modifier;

		ans.childInfos.push_back({});
		ans.childInfos.back().node = generator.get();
		if (activeOnly) {
			ans.childInfos.back().syncToParent = true;
			ans.syncToParent = true;
		}

		if (modifierAdded) {
			ans.childInfos.push_back({});
			ans.childInfos.back().node = modifier.get();

			if (activeOnly) {
				ans.childInfos.back().syncToParent = 0;
			}
		}
	}

	hkbNode* hkbModifierGenerator::cloneNode(hkbBehaviorGraph&) const
	{
		return new hkbModifierGenerator(*this);
	}

	void hkbModifierGenerator::generate(const hkbContext& a_context, const hkbGeneratorOutput** activeChildrenOutput, hkbGeneratorOutput& output, float timeOffset) const
	{
		using func_t = decltype(&hkbModifierGenerator::generate);
		REL::Relocation<func_t> func{ RELOCATION_ID(58900, 0) };
		return func(this, a_context, activeChildrenOutput, output, timeOffset);
	}

	void hkbModifierGenerator::updateSync(const hkbContext& ctx, hkbNodeInfo& info)
	{
		auto& generator_info = hkbUtils::get_active_info(ctx, generator.get());
		auto& generator_info_adjusted = hkbUtils::adjust_info_usesomeind(ctx, generator_info);
		info.syncInfo = generator_info_adjusted.syncInfo;

		if (modifier && modifier->enable) {
			auto modifierClass = modifier->GetClassType();
			if (modifierClass == &hkbModifierList::staticClass() || modifierClass == &BSTweenerModifier::staticClass()) {
				auto modifierClone = static_cast<hkbModifier*>(ctx.character->behaviorGraph->getNodeClone(modifier.get()));
				modifierClone->modifySyncInfo(ctx, info.syncInfo);
			}
		}
	}

	hkbModifierGenerator::hkbModifierGenerator(const hkbModifierGenerator& other) :
		modifier(other.modifier), generator(other.generator)
	{
		stl::emplace_vtable(this);
		userData |= 1;
	}
}
