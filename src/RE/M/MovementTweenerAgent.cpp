#include "RE/M/MovementTweenerAgent.h"

namespace RE
{
	const BSFixedString& IMovementTweenerAgent::QPipelineStage()
	{
		return *REL::Relocation<BSFixedString*>(RELOCATION_ID(525896, 412373));
	}

	MovementTweenerAgent::MovementTweenerAgent() :
		MovementAgent()
	{
		stl::emplace_vtable(this);
	}

	IPipelineStageInterface* MovementTweenerAgent::GetPipelineStageInterface(const BSFixedString& stage)
	{
		if (stage == QPipelineStage())
			return this;
		else
			return nullptr;
	}

	const BSFixedString& MovementTweenerAgent::GetTweenerAgentType() const
	{
		return GetAgentType();
	}

	void MovementTweenerAgent::GetTransform(const NiTransform& data, NiTransform& ans) const
	{
		ans = data;
	}
}
