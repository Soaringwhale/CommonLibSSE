#include "RE/M/MovementControllerAI.h"

namespace RE
{
	bool RE::MovementControllerAI::ActivateSet(const MovementControllerActiveSetDescription& set)
	{
		using func_t = decltype(&MovementControllerAI::ActivateSet);
		REL::Relocation<func_t> func{ RELOCATION_ID(89414, 91885) };
		return func(this, set);
	}

	bool MovementControllerAI::GetMovementAgent(const BSFixedString& type, MovementAgentPtr& ans) const
	{
		for (auto& agent : agents) {
			if (FindAgentByNameFunctor(agent.Qptr().get(), type)) {
				ans = agent.Qptr();
				return true;
			}
		}
		return false;
	}

	bool MovementControllerAI::FindAgentByNameFunctor(const MovementAgent* agent, const BSFixedString& type)
	{
		return agent && agent->GetAgentType() == type;
	}
}
