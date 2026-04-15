#pragma once

#include "RE/B/BGSNamedPackageData.h"
#include "RE/I/IPackageData.h"

namespace RE
{
	class BGSPackageDataBool : public BGSNamedPackageData<IPackageData>
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSPackageDataBool;

		~BGSPackageDataBool() override;  // 00

		// override (BGSNamedPackageData<IPackageData>)
		void                               Load(TESFile* a_mod) override;                                    // 02
		void                               Copy(const IPackageData* a_other) override;                       // 03
		bool                               Compare(const IPackageData* a_other) const override;              // 04
		void                               Validate(BGSPackageDataValidationContext& a_context) override;    // 05 - { return 1; }
		void                               SaveGame(BGSSaveFormBuffer* a_buf) override;                      // 07
		void                               LoadGame(BGSLoadFormBuffer* a_buf) override;                      // 08
		void                               InitLoadGame(BGSLoadFormBuffer* a_buf) override;                  // 09 - { return; }
		void                               GetDescription(BSString& a_dst, TESForm* a_form) const override;  // 0A
		[[nodiscard]] const BSFixedString& QType() const override;                                           // 0B - { return "Bool"; }
	};
	//static_assert(offsetof(BGSPackageDataBool, data) == 0x08);
	static_assert(sizeof(BGSPackageDataBool) == 0x10);
}
