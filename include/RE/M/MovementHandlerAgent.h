#pragma once

#include "RE/I/IPipelineStageInterface.h"
#include "RE/M/MovementAgent.h"

namespace RE
{
	struct MovementHandlerAgentUpdateDataSmallDelta;

	struct IMovementHandlerAgent : public IPipelineStageInterface
	{
		inline static constexpr auto RTTI = RTTI_IMovementHandlerAgent;
		inline static constexpr auto VTABLE = VTABLE_IMovementHandlerAgent;

		static const BSFixedString& QPipelineStage();

		~IMovementHandlerAgent() override = default;  // 00

		IMovementHandlerAgent();

		// add
		virtual const BSFixedString& GetHandlerAgentType() const = 0;                                                          // 01
		virtual void                 UpdateSmallDelta(const MovementHandlerAgentUpdateDataSmallDelta& agent_update_data) = 0;  // 02
		virtual void                 UpdateLargeDelta(void) = 0;                                                               // 03
	};
	static_assert(sizeof(IMovementHandlerAgent) == 0x8);

	class MovementHandlerAgent : public MovementAgent, public IMovementHandlerAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementHandlerAgent;
		inline static constexpr auto VTABLE = VTABLE_MovementHandlerAgent;

		MovementHandlerAgent();

		~MovementHandlerAgent() override = default;  // 00

		// override (MovementAgent)
		IPipelineStageInterface* GetPipelineStageInterface(const BSFixedString& stage) override;  // 03

		// override (IMovementHandlerAgent)
		const BSFixedString& GetHandlerAgentType() const override;  // 01
	};
	static_assert(sizeof(MovementHandlerAgent) == 0x20);
}
