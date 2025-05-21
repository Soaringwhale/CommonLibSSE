#include "RE/M/MovementHandlerAgent.h"

namespace RE
{
	IMovementHandlerAgent::IMovementHandlerAgent()
	{
		stl::emplace_vtable(this);
	}

	const BSFixedString& IMovementHandlerAgent::QPipelineStage()
	{
		return *REL::Relocation<BSFixedString*>(RELOCATION_ID(525843, 412320));
	}

	MovementHandlerAgent::MovementHandlerAgent() :
		MovementAgent()
	{
		stl::emplace_vtable(this);
	}

	IPipelineStageInterface* MovementHandlerAgent::GetPipelineStageInterface(const BSFixedString& stage)
	{
		if (stage == QPipelineStage())
			return this;
		else
			return nullptr;
	}

	const BSFixedString& MovementHandlerAgent::GetHandlerAgentType() const
	{
		return GetAgentType();
	}
}
