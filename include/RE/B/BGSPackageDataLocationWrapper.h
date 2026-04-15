
#pragma once

#include "RE/I/IPackageDataAIWorldLocationHandle.h"

namespace RE
{
	class BGSPackageDataLocationWrapper : public IPackageDataAIWorldLocationHandle
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSPackageDataLocationWrapper;

		~BGSPackageDataLocationWrapper() override; // 00

		// override (IAIWorldLocationHandle)
		const IAIWorldLocation* AllocateLocation(AIWorldLocationContext& a_context) const override;                       // 01
		const PackageLocation*  GetAsPackageLocation() const override;                                                    // 02
		bool                    IsRefAtLocation(AIWorldLocationContext& a_context, TESObjectREFR* a_ref) const override;  // 03

		// override (IPackageData)
		void                               InitItem(TESForm* a_form) override;                                                       // 01
		void                               Load(TESFile* a_mod) override;                                                            // 02
		void                               Copy(const IPackageData* a_other) override;                                               // 03
		bool                               Compare(const IPackageData* a_other) const override;                                      // 04
		void                               Validate(BGSPackageDataValidationContext& a_context) override;                            // 05
		void                               RemapInterruptData(std::uint32_t a_target, std::uint32_t a_loc, void* a_handle) override; // 06
		void                               SaveGame(BGSSaveFormBuffer* a_buf) override;                                              // 07
		void                               LoadGame(BGSLoadFormBuffer* a_buf) override;                                              // 08
		void                               InitLoadGame(BGSLoadFormBuffer* a_buf) override;                                          // 09
		void                               GetDescription(BSString& a_dst, TESForm* a_form) const override;                          // 0A
		[[nodiscard]] const BSFixedString& QType() const override;                                                                   // 0B
		bool                               QIsCurrLoc() override;                                                                    // 0C 

		// members
		IAIWorldLocation* wrappedLocation;   // 10
	};
	static_assert(sizeof(BGSPackageDataLocationWrapper) == 0x18);
}
