#pragma once

#include "RE/B/BSOcclusionShape.h"
#include "RE/N/NiFrustumPlanes.h"

namespace RE
{
	class BSMultiBoundShape;

	class BSOcclusionBox : public BSOcclusionShape
	{
	public:
		~BSOcclusionBox() override;  // 00

		// override (NiObject)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17

		// override (BSOcclusionShape)
		bool GetIsPlane() const override;  // 25 - { return false; }
		bool GetIsBox() const override;    // 26 - { return true; }

		// members
		NiPoint3           P2;                     // 48
		NiFrustumPlanes    planes[2];              // 54
		NiPoint3           vertices[8];            // 134
		char               pad194[4];              // 194
		BSMultiBoundShape* shape;                  // 198
		uint8_t            unk1A0[0x1E8 - 0x1A0];  // 1A0
	};
	static_assert(sizeof(BSOcclusionBox) == 0x1e8);
}
