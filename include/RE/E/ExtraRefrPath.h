#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class ExtraRefrPath : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraRefrPath;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kRefrPath;
		inline static constexpr auto VTABLE = VTABLE_ExtraRefrPath;

		enum class PATH_TYPE : uint32_t
		{
			Translation,
			Spline,
		};

		ExtraRefrPath()
		{
			stl::emplace_vtable(this);
		}

		~ExtraRefrPath() override = default;  // 00

		// override (BSExtraData)
		[[nodiscard]] ExtraDataType GetType() const override { return ExtraDataType::kRefrPath; };  // 01

		// members
		NiPoint3  startPos;               // 10
		NiPoint3  startTangent;           // 1C
		NiPoint3  startEuler;             // 28
		NiPoint3  goalPos;                // 34
		NiPoint3  goalTangent;            // 40
		NiPoint3  goalEuler;              // 4C
		float     speed;                  // 58
		float     maxRotSpeed;            // 5C
		float     currentParameter{ 0 };  // 60
		PATH_TYPE type;                   // 64
	};
	static_assert(sizeof(ExtraRefrPath) == 0x68);
}
