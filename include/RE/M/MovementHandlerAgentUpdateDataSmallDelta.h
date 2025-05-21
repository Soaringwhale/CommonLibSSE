#pragma once

namespace RE
{
	struct MovementHandlerOutputDataSmallDelta;
	struct MovementHandlerUpdateDataSmallDelta;

	struct MovementHandlerAgentUpdateDataSmallDelta
	{
		MovementHandlerAgentUpdateDataSmallDelta(MovementHandlerUpdateDataSmallDelta& a_update_data, MovementHandlerOutputDataSmallDelta& a_output) :
			update_data(&a_update_data), output(&a_output)
		{
		}

		// members
		MovementHandlerUpdateDataSmallDelta* update_data;  // 00
		MovementHandlerOutputDataSmallDelta* output;       // 08
	};
	static_assert(sizeof(MovementHandlerAgentUpdateDataSmallDelta) == 0x10);
}
