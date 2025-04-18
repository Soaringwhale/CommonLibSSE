#include "RE/B/BSiStateTaggingGenerator.h"

#include "RE/H/hkbBehaviorGraph.h"
#include "RE/H/hkbGeneratorOutputUtils.h"
#include "RE/H/hkbNodeInfo.h"
#include "RE/H/hkbUtils.h"

namespace RE
{
	void BSiStateTaggingGenerator::getChildren(GET_CHILDREN_FLAGS, ChildrenInfo& ans)
	{
		if (pDefaultGenerator) {
			ans.childInfos.push_back({});
			ans.childInfos.back().node = pDefaultGenerator;
			ans.childInfos.back().syncToParent = true;
			ans.syncToParent = true;
		}
	}

	void BSiStateTaggingGenerator::generate(const hkbContext&, const hkbGeneratorOutput** activeChildrenOutput, hkbGeneratorOutput& output, float) const
	{
		auto _activeChildrenOutput = *activeChildrenOutput;
		if (_activeChildrenOutput || &output != _activeChildrenOutput) {
			hkbGeneratorOutputUtils::copyGeneratorOutput(*_activeChildrenOutput, output);
		}
	}

	void BSiStateTaggingGenerator::updateSync(const hkbContext& ctx, hkbNodeInfo& info)
	{
		if (!pDefaultGenerator)
			return hkbGenerator::updateSync(ctx, info);

		auto& generator_info = hkbUtils::get_active_info(ctx, pDefaultGenerator);
		auto& generator_info_adjusted = hkbUtils::adjust_info_usesomeind(ctx, generator_info);
		info.syncInfo = generator_info_adjusted.syncInfo;
	}
}
