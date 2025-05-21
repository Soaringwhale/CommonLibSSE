#include "RE/N/NullMovementState.h"

#include "RE/N/NiPoint3.h"

namespace RE
{
	NullMovementState& NullMovementState::QInstance()
	{
		using func_t = decltype(&NullMovementState::QInstance);
		REL::Relocation<func_t> func{ RELOCATION_ID(89473, 0) };
		return func();
	}
	void NullMovementState::DoGetLocation(NiPoint3& pos) const
	{
		pos = RE::NiPoint3();
	}
	void NullMovementState::DoGetEulerAngles(NiPoint3& angles) const
	{
		angles = RE::NiPoint3();
	}
	IMovementParameters& NullMovementState::DoGetDefaultMovementParameters() const
	{
		using func_t = decltype(&NullMovementState::DoGetDefaultMovementParameters);
		REL::Relocation<func_t> func{ RELOCATION_ID(88523, 90949) };
		return func(this);
	}
}
