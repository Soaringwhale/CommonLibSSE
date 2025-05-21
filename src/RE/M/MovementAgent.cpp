#include "RE/M/MovementAgent.h"

#include "RE/N/NullMovementState.h"

namespace RE
{
	MovementAgent::MovementAgent()
	{
		stl::emplace_vtable(this);
		movementState = &NullMovementState::QInstance();
	}
}
