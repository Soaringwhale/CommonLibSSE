#pragma once

#include "RE/N/NiSmartPointer.h"
#include "RE/T/TESObjectREFR.h"

namespace RE
{
	class ActionQueue;
	class ActorState;
	class BGSAction;
	class BGSAnimationSequencer;

	class ActionInput
	{
	public:
		inline static constexpr auto RTTI = RTTI_ActionInput;
		inline static constexpr auto VTABLE = VTABLE_ActionInput;

		enum class ACTIONPRIORITY : uint32_t
		{
			Priority_0,
			Priority_1,
			Priority_2,
		};

		ActionInput(ACTIONPRIORITY a_priority = ACTIONPRIORITY::Priority_0, TESObjectREFR* a_ref = nullptr, BGSAction* a_action = nullptr, TESObjectREFR* a_targetRef = nullptr) :
			ref(a_ref), targetRef(a_targetRef), action(a_action), priority(a_priority) { stl::emplace_vtable(this); }
		ActionInput(const ActionInput& other) = delete;

		virtual ~ActionInput() = default;  // 00

		// add
		virtual ActorState*            GetSourceActorState() const { return nullptr; }  // 01
		virtual ActionQueue*           GetActionQueue() { return nullptr; }             // 02
		virtual BGSAnimationSequencer* GetSourceSequencer() const { return nullptr; }   // 03

		TES_HEAP_REDEFINE_NEW();

		// members
		TESObjectREFRPtr ref{};                             // 08
		TESObjectREFRPtr targetRef{};                       // 10
		BGSAction*       action{ nullptr };                 // 18
		ACTIONPRIORITY   priority{ ACTIONPRIORITY::Priority_0 };  // 20

	protected:
		void CopyTo(ActionInput& dst) const
		{
			dst.ref = ref;
			dst.targetRef = targetRef;
			dst.action = action;
			dst.priority = priority;
		}
	};
	static_assert(sizeof(ActionInput) == 0x28);
}
