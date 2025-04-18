#pragma once

namespace RE
{
	class hkbContext;
	class hkbNode;
	struct hkbNodeInfo;

	namespace hkbUtils
	{
		hkbNodeInfo& get_active_info(const hkbContext& ctx, hkbNode* nodeClone);
		hkbNodeInfo& adjust_info_usesomeind(const hkbContext& ctx, hkbNodeInfo& info);
	}
}
