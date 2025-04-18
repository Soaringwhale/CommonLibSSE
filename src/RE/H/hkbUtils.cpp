#include "RE/H/hkbUtils.h"

#include "RE/H/hkbBehaviorGraph.h"
#include "RE/H/hkbContext.h"

namespace RE
{
	namespace hkbUtils
	{
		hkbNodeInfo& get_active_info(const hkbContext& ctx, hkbNode* nodeClone)
		{
			return ctx.character->behaviorGraph->accessNodeInfoByClone(nodeClone);
		}

		hkbNodeInfo& adjust_info_usesomeind(const hkbContext& ctx, hkbNodeInfo& info)
		{
			return ctx.character->behaviorGraph->adjust_info_usesomeind(info);
		}
	}
}
