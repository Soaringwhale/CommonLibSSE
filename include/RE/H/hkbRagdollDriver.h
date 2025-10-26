#pragma once

#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkaRagdollInstance;

	// TODO: fix dtor
	class hkbRagdollDriver : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbRagdollDriver;
		inline static constexpr auto VTABLE = VTABLE_hkbRagdollDriver;

		hkbRagdollDriver(hkbCharacter* hchar, bool field_1C) :
			unk1C(field_1C), character(hchar)
		{
			stl::emplace_vtable(this);
		}

		// TODO: implement setRagdollInterface(nullptr) and deallocs
		~hkbRagdollDriver() override = default;  // 00

		// members
		float                         unk10{ 0 };               // 10
		int32_t                       unk14{ -1 };              // 14
		int16_t                       unk18{ -1 };              // 18
		uint8_t                       unk1A{ 0 };               // 1A
		uint8_t                       unk1B{ 0 };               // 1B
		bool                          unk1C;                    // 1C
		uint8_t                       unk1D{ 0 };               // 1D
		uint16_t                      pad1E;                    // 1E
		uint64_t                      unk20{ 0 };               // 20
		uint64_t                      unk28{ 0 };               // 28
		hkQuaternion                  unk30{ { 0, 0, 0, 1 } };  // 30
		hkVector4                     unk40{ 1, 1, 1, 1 };      // 40
		int32_t                       pad50{ -1 };              // 50
		int32_t                       pad54{ -1 };              // 54
		hkArray<int32_t>              reportingWhenKeyframed;   // 58
		uint32_t                      unk68{ 0 };               // 68
		uint32_t                      pad6C;                    // 6C
		hkPointerMap<void*, uint32_t> map;                      // 70
		hkbCharacter*                 character;                // 80
		hkaRagdollInstance*           ragdoll{ nullptr };       // 88
		uint64_t                      unk90{ 0 };               // 90
		uint64_t                      unk98{ 0 };               // 98
		void*                         unkA0{ 0 };               // A0 - easy allocated, need to deallocate
		void*                         unkA8{ 0 };               // A8 - need to deallocate
		uint32_t                      unkB0{ 0 };               // B0 - size of unkA8 in bytes = 0x30 * unkB0
		uint32_t                      unkB4{ 0 };               // B4
		uint32_t                      unkB8{ 0 };               // B8
		uint32_t                      padBC;                    // BC
		float                         unkC0{ 0 };               // C0
		uint8_t                       unkC4{ 1 };               // C4
		uint8_t                       unkC5{ 0 };               // C5
		uint8_t                       unkC6{ 1 };               // C6
		uint8_t                       unkC7{ 0 };               // C7
		uint8_t                       unkC8{ 0 };               // C8
		uint8_t                       unkC9{ 0 };               // C9
		uint8_t                       unkCA{ 0 };               // CA
		uint8_t                       unkCB{ 0 };               // CB
		uint32_t                      padCC;                    // CC
	};
	static_assert(sizeof(hkbRagdollDriver) == 0xD0);
}
