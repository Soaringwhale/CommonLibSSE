#pragma once

#include "RE/B/BSTArray.h"
#include "RE/M/MovementVector.h"
#include "RE/N/NiPoint3.h"
#include "RE/W/WeightedModifier.h"

namespace RE
{
	struct MovementHandlerUpdateDataSmallDelta;
	class MovementParameters;

	class MovementPlannerAgentReturnDataSmallDelta
	{
	public:
		// members
		WeightedModifier<MovementVector>     moving;                     // 00
		WeightedModifier<NiPoint3>           angles;                     // 14
		uint32_t                             unk24;                      // 24
		float                                unk28;                      // 28
		uint32_t                             unk2C;                      // 2C
		MovementParameters*                  movement_params;            // 30
		MovementHandlerUpdateDataSmallDelta* handler_update_data;        // 38
		BSScrapArray<void*>*                 handler_update_data_array;  // 40
		float                                field_48;                   // 48
		float                                field_4C;                   // 4C
		uint8_t                              field50;                    // 50
		uint8_t                              field51;                    // 51
		uint8_t                              pad52[6];                   // 52
	};
	static_assert(sizeof(MovementPlannerAgentReturnDataSmallDelta) == 0x58);
}
