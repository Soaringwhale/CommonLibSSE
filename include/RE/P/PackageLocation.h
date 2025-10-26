#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/I/IAIWorldLocationHandle.h"

namespace RE
{
	class BGSKeyword;
	class TESForm;
	class TESObjectCELL;

	class PackageLocation : public IAIWorldLocationHandle
	{
	public:
		inline static constexpr auto RTTI = RTTI_PackageLocation;
		inline static constexpr auto VTABLE = VTABLE_PackageLocation;

		enum class Type : uint8_t
		{
			kNone = static_cast<std::underlying_type_t<Type>>(-1),
			kNearReference = 0,
			kInCell = 1,
			kNearPackageStartLocation = 2,
			kNearEditorLocation = 3,
			kObjectID = 4,
			kObjectType = 5,
			kNearLinkedReference = 6,
			kAtPackagelocation = 7,
			kAlias_Reference = 8,
			kAlias_Location = 9,
			kUnkA = 0xA,
			kUnkB = 0xB,
			kNearSelf = 0xC,
		};

		union Data
		{
			Data() { unk8b = 0; }
			~Data() {}

			ObjectRefHandle locRefHandle;         // NearReference
			TESObjectCELL*  locCell;              // InCell
			TESForm*        locObject;            // ObjectID
			uint32_t        locObjectType;        // ObjectType, aka PACKAGE_OBJECT_TYPE
			BGSKeyword*     locLinkedRefKeyword;  // NearLinkedReference
			uint32_t        refAlias;             // Alias_Reference
			uint32_t        locAlias;             // Alias_Location
			uint32_t        interruptLoc;         // kUnkA, aka PACK_INTERRUPT_LOCATION
			uint8_t         packageTargetUID;     // kUnkB
			uint64_t        unk8b;                // rest
			FormID          formID;               // sometimes used
		};
		static_assert(sizeof(Data) == 0x8);

		PackageLocation();

		~PackageLocation() override;  // 00

		// override (IAIWorldLocationHandle)
		const IAIWorldLocation* AllocateLocation(AIWorldLocationContext& a_context) const override;                       // 01
		const PackageLocation*  GetAsPackageLocation() const override { return this; }                                    // 02
		bool                    IsRefAtLocation(AIWorldLocationContext& a_context, TESObjectREFR* a_ref) const override;  // 03

		// members
		Type     locType{ Type::kNearEditorLocation };  // 08
		uint8_t  pad09[3];                              // 09
		uint32_t radius{};                              // 0C
		Data     data;                                  // 10
	};
	static_assert(sizeof(PackageLocation) == 0x18);
}
