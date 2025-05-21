#pragma once

#include "RE/I/IPipelineStageInterface.h"
#include "RE/M/MovementAgent.h"

namespace RE
{
	struct MovementHandlerOutputDataSmallDelta;
	struct MovementTweenerAgentOutputData;

	struct IMovementTweenerAgent : public IPipelineStageInterface
	{
		inline static constexpr auto RTTI = RTTI_IMovementTweenerAgent;
		inline static constexpr auto VTABLE = VTABLE_IMovementTweenerAgent;

		static const BSFixedString& QPipelineStage();

		virtual ~IMovementTweenerAgent() override = default;  // 00

		// add
		virtual const BSFixedString& GetTweenerAgentType() const = 0;                                                                                       // 01
		virtual void                 GetTransform(const NiTransform& data, NiTransform& ans) const = 0;                                                     // 02
		virtual void                 Update(MovementHandlerOutputDataSmallDelta& handler_output_data, MovementTweenerAgentOutputData& tweener_output) = 0;  // 03
	};

	class MovementTweenerAgent : public MovementAgent, public IMovementTweenerAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementTweenerAgent;
		inline static constexpr auto VTABLE = VTABLE_MovementTweenerAgent;

		MovementTweenerAgent();

		~MovementTweenerAgent() override = default;  // 00

		// override (MovementAgent)
		IPipelineStageInterface* GetPipelineStageInterface(const BSFixedString& stage) override;  // 03

		// override (IMovementTweenerAgent)
		const BSFixedString& GetTweenerAgentType() const override;                                    // 01
		void                 GetTransform(const NiTransform& data, NiTransform& ans) const override;  // 02
	};
	static_assert(sizeof(MovementTweenerAgent) == 0x20);
}
