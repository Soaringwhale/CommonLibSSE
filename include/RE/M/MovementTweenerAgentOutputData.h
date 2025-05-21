#pragma once

namespace RE
{
	struct MovementTweenerAgentOutputData
	{
		// members
		NiPoint3  P;  // 00
		NiMatrix3 M;  // 0C
	};
	static_assert(sizeof(MovementTweenerAgentOutputData) == 0x30);
}
