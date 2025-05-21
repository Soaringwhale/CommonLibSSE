#pragma once

namespace RE
{
	struct MovementPlannerUpdateDataSmallDelta
	{
		// members
		float dtime;  // 00
	};
	static_assert(sizeof(MovementPlannerUpdateDataSmallDelta) == 0x4);
}
