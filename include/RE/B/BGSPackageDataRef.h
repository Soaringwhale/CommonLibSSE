
#pragma once

#include "RE/B/BGSNamedPackageData.h" 
#include "RE/I/IAITarget.h"


namespace RE
{
	class PackageTarget;
	struct AIWorldLocationContext;

	class BGSPackageDataRef : public IAITarget
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSPackageDataRef;
		
		~BGSPackageDataRef() override; // 00
		
		// override (IAIWorldLocationHandle / IAITarget vtable)
		const IAIWorldLocation* AllocateLocation(AIWorldLocationContext& a_context) const override;                      // 01
		bool                    IsRefAtLocation(AIWorldLocationContext& a_context, TESObjectREFR* a_ref) const override; // 03
		
		// override (IPackageData vtable)
		void                               InitItem(TESForm* a_form) override;                                // 01
		void                               Load(TESFile* a_mod) override;                                     // 02
		void                               Copy(const IPackageData* a_other) override;                        // 03
		bool                               Compare(const IPackageData* a_other) const override;               // 04
		void                               Validate(BGSPackageDataValidationContext* a_context) override;     // 05
		void                               GetDescription(BSString& a_dst, TESForm* a_form) const override;   // 0A
		[[nodiscard]] const BSFixedString& QType() const override;                                            // 0B
		
		// add
		virtual void InternalLoad(TESFile* a_mod);    // 0C
		
		// members
		BSFixedString  dataName;       // 10
		PackageTarget* packageTarget;  // 18
	};
	static_assert(sizeof(BGSPackageDataRef) == 0x20);
}
