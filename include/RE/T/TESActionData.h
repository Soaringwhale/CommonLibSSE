#pragma once

#include "RE/B/BGSActionData.h"

#include "RE/A/Actor.h"  // todo: remove when cpp

namespace RE
{
	class TESActionData : public BGSActionData
	{
	public:
		TESActionData(ACTIONPRIORITY a_priority = ACTIONPRIORITY::Priority_0, TESObjectREFR* a_ref = nullptr, BGSAction* a_action = nullptr, TESObjectREFR* a_targetRef = nullptr) :
			BGSActionData(a_priority, a_ref, a_action, a_targetRef)
		{
			stl::emplace_vtable(this);
		}

		virtual ~TESActionData() override = default;  // 00

		// override (ActionInput)
		// 01
		ActorState*            GetSourceActorState() const override { 
			if (!ref)
				return nullptr;

			if (auto a = ref->As<Actor>()) {
				return a;
			} else {
				return nullptr;
			}
		}
		ActionQueue*           GetActionQueue(void) override { return nullptr; }         // 02
																		// 03
		BGSAnimationSequencer* GetSourceSequencer() const override
		{
			return ref ? ref->GetSequencer() : nullptr;
		}

		// override (BGSActionData)
		BGSActionData* CreateCopy() const override { return nullptr; }  // 04
																   // 05
		bool DoIt() override
		{
			using func_t = decltype(&TESActionData::DoIt);
			REL::Relocation<func_t> func{ RELOCATION_ID(40551, 41557) };
			return func(this);
		}
	};
	static_assert(sizeof(TESActionData) == 0x60);
}
