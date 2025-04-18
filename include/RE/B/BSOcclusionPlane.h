#pragma once

#include "RE/B/BSOcclusionShape.h"
#include "RE/N/NiFrustumPlanes.h"
#include "RE/N/NiPoint2.h"

namespace RE
{
	class BSOcclusionPlane : public BSOcclusionShape
	{
	public:
		~BSOcclusionPlane() override;  // 00

		// override (NiObject)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17

		// override (BSOcclusionShape)
		bool GetIsPlane() const override;  // 25 - { return true; }
		bool GetIsBox() const override;    // 26 - { return false; }

		// members
		NiPoint2        P2;           // 048
		NiFrustumPlanes planes;       // 050
		NiPoint3        vertices[4];  // 0C0
		bool            fieldF0[4];   // 0F0
		bool            fieldF4;      // 0F4
		char            padF5[3];     // 0F5
		uint64_t        unkF8;        // 0F8
		uint64_t        unk100;       // 100
		uint64_t        unk108;       // 108
		uint64_t        unk110;       // 110
	};
	static_assert(sizeof(BSOcclusionPlane) == 0x118);
}
