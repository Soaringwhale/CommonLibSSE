#pragma once

#include "RE/I/IPipelineStageInterface.h"
#include "RE/M/MovementAgent.h"

namespace RE
{
	class MovementPlannerAgentReturnDataSmallDelta;
	struct MovementPlannerUpdateDataSmallDelta;

	struct IMovementPlannerAgent : public IPipelineStageInterface
	{
		inline static constexpr auto RTTI = RTTI_IMovementPlannerAgent;
		inline static constexpr auto VTABLE = VTABLE_IMovementPlannerAgent;

		static const BSFixedString& QPipelineStage();

		IMovementPlannerAgent();

		virtual ~IMovementPlannerAgent() override = default;  // 00

		// add
		virtual const BSFixedString& GetPlannerAgentType() const = 0;                                                                                                      // 01
		virtual void                 UpdateSmallDelta(const MovementPlannerUpdateDataSmallDelta& update_data, MovementPlannerAgentReturnDataSmallDelta& return_data) = 0;  // 02
		virtual void                 UpdateLargeDelta(void) = 0;                                                                                                           // 03
	};

	class MovementPlannerAgent : public MovementAgent, public IMovementPlannerAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementPlannerAgent;
		inline static constexpr auto VTABLE = VTABLE_MovementPlannerAgent;

		MovementPlannerAgent();

		~MovementPlannerAgent() override = default;  // 00

		// override (MovementAgent)
		IPipelineStageInterface* GetPipelineStageInterface(const BSFixedString& stage) override;  // 03

		// override (IMovementPlannerAgent)
		const BSFixedString& GetPlannerAgentType() const override;  // 01
	};
	static_assert(sizeof(MovementPlannerAgent) == 0x20);
}
