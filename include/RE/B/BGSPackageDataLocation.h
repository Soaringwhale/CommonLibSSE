#pragma once

#include "RE/B/BGSPackageDataPointerTemplate.h"
#include "RE/I/IPackageDataAIWorldLocationHandle.h"

namespace RE
{
	class PackageLocation;

	//const BSFixedString kPackageDataLocationTypeName("Location");

	class BGSPackageDataLocation : public BGSPackageDataPointerTemplate<IPackageDataAIWorldLocationHandle, PackageLocation /*, kPackageDataLocationTypeName*/>
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSPackageDataLocation;

		~BGSPackageDataLocation() override;  // 00

		// override (BGSPackageDataPointerTemplate<IPackageDataAIWorldLocationHandle, PackageLocation, kPackageDataLocationTypeName>)
		void RemapInterruptData(std::uint32_t a_target, std::uint32_t a_loc, void* a_handle) override;  // 06
		void SaveGame(BGSSaveFormBuffer* a_buf) override;                                               // 07
		void LoadGame(BGSLoadFormBuffer* a_buf) override;                                               // 08
		void InitLoadGame(BGSLoadFormBuffer* a_buf) override;                                           // 09 - { return; }
		void GetDescription(BSString& a_dst, TESForm* a_form) const override;                           // 0A
		bool QIsCurrLoc() override;                                                                     // 0C - { return pointer->type == PackageLocation::Type::kNearPackageStartLocation; }
	};
	static_assert(sizeof(BGSPackageDataLocation) == 0x20);
}
