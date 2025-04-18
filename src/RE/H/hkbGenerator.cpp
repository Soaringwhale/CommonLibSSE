#include "RE/H/hkbGenerator.h"

#include "RE/H/hkbNodeInfo.h"

namespace RE
{
	void hkbGenerator::updateSync(const hkbContext&, hkbNodeInfo& info)
	{
		info.syncInfo.playbackSpeed = 1.0f;
		info.syncInfo.numSyncPoints = 0;
		info.syncInfo.duration = 0;
		info.syncInfo.localTime = 0;
	}
}
