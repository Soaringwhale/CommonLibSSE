#include "RE/P/PackageLocation.h"

namespace RE
{
	PackageLocation::PackageLocation()
	{
		stl::emplace_vtable(this);
	}

	PackageLocation::~PackageLocation()
	{
		locType = Type::kNone;
		radius = 0;
		data.unk8b = 0;
	}

	const IAIWorldLocation* PackageLocation::AllocateLocation(AIWorldLocationContext& a_context) const
	{
		using func_t = decltype(&PackageLocation::AllocateLocation);
		REL::Relocation<func_t> func{ RELOCATION_ID(29012, 29820) };
		return func(this, a_context);
	}

	bool PackageLocation::IsRefAtLocation(AIWorldLocationContext& a_context, TESObjectREFR* a_ref) const
	{
		using func_t = decltype(&PackageLocation::IsRefAtLocation);
		REL::Relocation<func_t> func{ RELOCATION_ID(29013, 29821) };
		return func(this, a_context, a_ref);
	}
}
