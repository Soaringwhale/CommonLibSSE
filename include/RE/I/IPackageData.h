#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSString.h"

namespace RE
{
	class BGSLoadFormBuffer;
	class TESFile;
    class BGSPackageDataValidationContext;

	class IPackageData
	{
	public:
		inline static constexpr auto RTTI = RTTI_IPackageData;

		virtual ~IPackageData();  // 00

		virtual void                               InitItem(TESForm* a_form) = 0;                                                   // 01
		virtual void                               Load(TESFile* a_mod) = 0;                                                        // 02
		virtual void                               Copy(const IPackageData* a_other) = 0;                                           // 03
		virtual bool                               Compare(const IPackageData* a_other) const = 0;                                  // 04
		virtual void                               Validate(BGSPackageDataValidationContext* a_context) = 0;                        // 05 
		virtual void                               RemapInterruptData(std::uint32_t a_target, std::uint32_t a_loc, void* a_handle); // 06
		virtual void                               SaveGame(BGSSaveFormBuffer* a_buf);                                              // 07
		virtual void                               LoadGame(BGSLoadFormBuffer* a_buf);                                              // 08
		virtual void                               InitLoadGame(BGSLoadFormBuffer* a_buf);                                          // 09
		virtual void                               GetDescription(BSString& a_dst, TESForm* a_form) const = 0;                      // 0A
		[[nodiscard]] virtual const BSFixedString& QType() const = 0;                                                               // 0B
		virtual bool                               QIsCurrLoc();                                                                    // 0C
	};
	static_assert(sizeof(IPackageData) == 0x8);
}
