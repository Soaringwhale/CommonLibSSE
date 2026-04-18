
#pragma once

#include "RE/B/BGSNamedPackageData.h" 
#include "RE/I/IAITarget.h"


namespace RE
{
	class PackageTarget;
	struct AIWorldLocationContext;

	class BGSPackageDataRef : public BGSNamedPackageData<IAITarget>
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSPackageDataRef;

		~BGSPackageDataRef() override;  // 00

		// override (IAITarget)
		const IAIWorldLocation* AllocateLocation(AIWorldLocationContext& a_context) const override;                        // 01
		bool                    IsRefAtLocation(AIWorldLocationContext& a_context, TESObjectREFR* a_ref) const override;   // 03
		void*                   GetRefOrContainer(AITargetContext& a_context) override;                                    // 04
		void*                   GetObjectA(AITargetContext& a_context) override;                                           // 05
		std::uint32_t           GetAcquireType() override;                                                                 // 06
		bool                    IsValidTarget(AITargetContext& a_context, const TESObjectREFR* a_ref) override;            // 07
		bool                    GetHasFurtherTargets() override;                                                           // 08
		void                    AdvanceToNextTarget() override;                                                            // 09
		std::uint32_t           GetCount() override;                                                                       // 0A

		// override (IPackageData)
		void							   Validate(BGSPackageDataValidationContext& a_context) override;                              // 05
		void							   RemapInterruptData(std::uint32_t a_target, std::uint32_t a_loc, void* a_handle) override;   // 06
		void							   SaveGame(BGSSaveFormBuffer* a_buf) override;                                                // 07
		void							   LoadGame(BGSLoadFormBuffer* a_buf) override;                                                // 08
		void							   InitLoadGame(BGSLoadFormBuffer* a_buf) override;                                            // 09
		void							   GetDescription(BSString& a_dst, TESForm* a_form) const override;                            // 0A
		[[nodiscard]] const BSFixedString& QType() const override;																	   // 0B

		// add
		virtual void InternalLoad(TESFile* a_mod);  // 0C

		// members
		PackageTarget* packageTarget;  // 18
	};
	static_assert(sizeof(BGSPackageDataRef) == 0x20);
	static_assert(offsetof(BGSPackageDataRef, packageTarget) == 0x18);
}
