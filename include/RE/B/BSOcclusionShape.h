#pragma once

#include "RE/N/NiObject.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class BSOcclusionShape : public NiObject
	{
	public:
		~BSOcclusionShape() override;  // 00

		// override (NiObject)
		const NiRTTI* GetRTTI() const override;                           // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17

		// add
		virtual bool GetIsPlane() const = 0;  // 25
		virtual bool GetIsBox() const = 0;    // 26

		// members
		NiPoint3  P;         // 10
		NiMatrix3 M;         // 1C
		uint32_t  unk40;     // 40
		uint8_t   unk44;     // 44
		char      pad45[3];  // 45
	};
	static_assert(sizeof(BSOcclusionShape) == 0x48);
}
