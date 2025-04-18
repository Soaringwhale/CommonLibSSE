#pragma once

#include "RE/A/AnimationSystemUtils.h"
#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"
#include "RE/T/TESActionData.h"

namespace RE
{
	class Actor;
	class BGSAction;
	class NiPoint3;

	class CombatAnimation : public TESActionData
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESActionData;
		inline static constexpr auto VTABLE = VTABLE_TESActionData;

		enum ANIM : uint32_t
		{
			kActionRightAttack,
			kActionRightRelease,
			kActionRightPowerAttack,
			kActionLeftAttack,
			kActionLeftRelease,
			kActionRightAttack2,   // ranged?
			kActionRightRelease2,  // ranged?
			kActionRightInterrupt,
			kActionSneak,
			kActionActivate
		};

		enum class LoadedStatus : uint32_t
		{
			kNone,
			kSuccess,
			kFail
		};

		CombatAnimation(Actor* actor, ANIM anim);
		CombatAnimation(Actor* actor, TESObjectREFR* target, ANIM anim);
		CombatAnimation(Actor* actor, BGSAction* action);

		static bool Execute(Actor* actor, ANIM anim);
		static bool Execute(Actor* actor, TESObjectREFR* target, ANIM anim);

		bool  Check();
		bool  Execute();  // { return Process(); }
		bool  GetEventData(const BSFixedString& event_name, float& event_time);
		bool  GetEventData(const BSFixedString& event_name, float& event_time, NiPoint3& translation);
		float GetEventTime(const BSFixedString& event_name);
		float GetLength();
		bool  GetTranslation(NiPoint3& translation);
		bool  LoadClipData();

		// members
		BSScrapArray<AnimationSystemUtils::UtilsClipData> data;                            // 60
		LoadedStatus                                      status{ LoadedStatus ::kNone };  // 80
		uint32_t                                          pad84;                           // 84

	private:
		static const DEFAULT_OBJECT* QCombatAnimationActionArray()
		{
			return &*REL::Relocation<DEFAULT_OBJECT*>(RELOCATION_ID(509673, 0).address());  // doi ae
		}
	};
	static_assert(sizeof(CombatAnimation) == 0x88);
}
