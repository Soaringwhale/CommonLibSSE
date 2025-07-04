#pragma once

namespace RE
{
	class IAIWorldLocation;
	class PackageLocation;
	class TESObjectREFR;
	struct AIWorldLocationContext;

	class IAIWorldLocationHandle
	{
	public:
		inline static constexpr auto RTTI = RTTI_IAIWorldLocationHandle;

		virtual ~IAIWorldLocationHandle() = default;  // 00

		// add
		virtual const IAIWorldLocation* AllocateLocation(AIWorldLocationContext& a_context) const = 0;                       // 01
		virtual const PackageLocation*  GetAsPackageLocation() const { return nullptr; };                                    // 02
		virtual bool                    IsRefAtLocation(AIWorldLocationContext& a_context, TESObjectREFR* a_ref) const = 0;  // 03
	};
	static_assert(sizeof(IAIWorldLocationHandle) == 0x8);
}
