#pragma once

#include "RE/A/ActionInput.h"
#include "RE/A/ActionOutput.h"

namespace RE
{
	class BGSActionData :
		public ActionInput,  // 00
		public ActionOutput  // 28
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSActionData;
		inline static constexpr auto VTABLE = VTABLE_BGSActionData;

		enum class Flag : uint32_t
		{
			Flag1 = 1 << 0,
			Flag2 = 1 << 1,
		};
		using Flags = stl::enumeration<Flag, uint32_t>;

		BGSActionData(ACTIONPRIORITY a_priority = ACTIONPRIORITY::Priority_0, TESObjectREFR* a_ref = nullptr, BGSAction* a_action = nullptr, TESObjectREFR* a_targetRef = nullptr) :
			ActionInput(a_priority, a_ref, a_action, a_targetRef)
		{
			stl::emplace_vtable(this);
		}

		virtual ~BGSActionData() override = default;  // 00

		// add
		// 04
		virtual BGSActionData* CreateCopy() const
		{
			auto ans = new BGSActionData();

			BGSActionData::CopyTo(*ans);

			return ans;
		}
		virtual bool DoIt() { return false; };  // 05

		void CopyTo(class BGSActionData& dst) const
		{
			ActionInput::CopyTo(dst);
			ActionOutput::CopyTo(dst);

			dst.flags = flags;
		}

		// members
		Flags flags{};  // 58
	};
	static_assert(sizeof(BGSActionData) == 0x60);
}
