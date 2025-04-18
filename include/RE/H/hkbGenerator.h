#pragma once

#include "RE/H/hkbNode.h"

namespace RE
{
	struct hkbGeneratorOutput;
	struct hkbNodeInfo;

	class hkbGenerator : public hkbNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbGenerator;
		inline static constexpr auto VTABLE = VTABLE_hkbGenerator;

		hkbGenerator() { stl::emplace_vtable(this); }
		~hkbGenerator() override = default;  // 00

		// override (hkbNode)
		bool isGenerator() const override { return 1; }  // 15

		// add
		virtual void generate(const hkbContext& a_context, const hkbGeneratorOutput** activeChildrenOutput, hkbGeneratorOutput& output, float timeOffset = 0.0f) const = 0;  // 17
		virtual bool canRecycleOutput() const { return false; }                                                                                                              // 18
		virtual void updateSync(const hkbContext& a_context, hkbNodeInfo& info);                                                                                             // 19
		virtual void setLocalTime([[maybe_unused]] float time) {};                                                                                                           // 1A
		virtual void startEcho() {};                                                                                                                                         // 1B

		HK_HEAP_REDEFINE_NEW();
	};
	static_assert(sizeof(hkbGenerator) == 0x48);
}
