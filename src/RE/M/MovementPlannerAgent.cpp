#include "RE/M/MovementPlannerAgent.h"

namespace RE
{
	const BSFixedString& IMovementPlannerAgent::QPipelineStage()
	{
		return *REL::Relocation<BSFixedString*>(RELOCATION_ID(525852, 412329));
	}

	IMovementPlannerAgent::IMovementPlannerAgent()
	{
		stl::emplace_vtable(this);
	}

	MovementPlannerAgent::MovementPlannerAgent() :
		MovementAgent()
	{
		stl::emplace_vtable(this);
	}

	IPipelineStageInterface* MovementPlannerAgent::GetPipelineStageInterface(const BSFixedString& stage)
	{
		if (stage == QPipelineStage())
			return this;
		else
			return nullptr;
	}

	const BSFixedString& MovementPlannerAgent::GetPlannerAgentType() const
	{
		return GetAgentType();
	}
}
