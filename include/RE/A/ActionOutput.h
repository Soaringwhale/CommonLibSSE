#pragma once

#include "RE/B/BSFixedString.h"

namespace RE
{
	class TESIdleForm;

	class ActionOutput
	{
	public:
		inline static constexpr auto RTTI = RTTI_ActionOutput;

		ActionOutput() = default;
		~ActionOutput() = default;
		ActionOutput(const ActionOutput& other) = delete;

		// members
		BSFixedString animEvent{};             // 00
		BSFixedString targetAnimEvent{};       // 08
		int32_t       result{ 0 };             // 10
		char          pad14[4];                // 14
		TESIdleForm*  sequence{ nullptr };     // 18
		TESIdleForm*  animObjIdle{ nullptr };  // 20
		uint32_t      sequenceIndex{ 0 };      // 28
		char          pad2C[4];                // 2C

	protected:
		void CopyTo(ActionOutput& dst) const
		{
			dst.animEvent = animEvent;
			dst.result = result;
			dst.sequence = sequence;
			dst.sequenceIndex = sequenceIndex;
		}
	};
	static_assert(sizeof(ActionOutput) == 0x30);
}
