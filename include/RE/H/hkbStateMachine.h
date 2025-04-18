#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkMap.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkbBehaviorGraph.h"
#include "RE/H/hkbBindable.h"
#include "RE/H/hkbCondition.h"
#include "RE/H/hkbEvent.h"
#include "RE/H/hkbGenerator.h"
#include "RE/H/hkbTransitionEffect.h"

namespace RE
{
	class hkbStateChooser;

	class hkbStateListener : public hkReferencedObject
	{
	};
	static_assert(sizeof(hkbStateListener) == 0x10);

	/// An interface to choose a state (typically the start state) of a state machine.
	class hkbStateChooser : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbStateChooser;
		inline static constexpr auto VTABLE = VTABLE_hkbStateChooser;

		hkbStateChooser()
		{
			stl::emplace_vtable(this);
		};

		/// Returns the ID of a state of the given state machine.
		virtual int chooseStateId(const hkbContext& context, const hkbStateMachine& stateMachine) = 0;
	};
	static_assert(sizeof(hkbStateChooser) == 0x10);

	// TODO: remove
	class BSiStateTaggingUtils__BSiStateTaggingStateListener : public hkbStateListener
	{
	public:
		// members
		uint32_t iState;    // 10
		uint32_t priority;  // 14
	};
	static_assert(sizeof(BSiStateTaggingUtils__BSiStateTaggingStateListener) == 0x18);

	/// A state machine that transitions between generators.
	///
	/// An hkbStateMachine organizes a set of states, each of which has an hkbGenerator.  The state machine is
	/// itself an hkbGenerator.  When not in a transition, it simply generates a pose by calling the generator
	/// corresponding to the current state.  During a transition, it generates poses using an hkbTransitionEffect to
	/// generate the pose (typically by blending the generator being transitioned from with the one being transitioned
	/// to.
	class hkbStateMachine : public hkbGenerator
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbStateMachine;
		inline static constexpr auto VTABLE = VTABLE_hkbStateMachine;

		// Ways of setting the start state.
		enum class StartStateMode
		{
			// Set the start state to m_startStateId.
			kDefault = 0,
			// Set the start state from the variable whose index is m_syncVariableIndex.
			kSync = 1,
			// Set the start state to a random state.
			kRandom = 2,
			// Set the start state using m_startStateChooser.
			kChooser = 3
		};

		// How to deal with self-transitions (when the state machine is transitioned to while still active).
		enum class StateMachineSelfTransitionMode
		{
			// Stay in the current state.
			kNoTransition = 0,
			// Transition to the start state if a transition exists between the current state and the start state.
			kTransitionToStartState = 1,
			// Transition to the start state using a transition if there is one, or otherwise by abruptly changing states.
			kForceTransitionToStartState = 2
		};

		class TransitionInfoArray;

		/// An array of EventProperties wrapped for shared access.
		class EventPropertyArray : public hkReferencedObject
		{
		public:
			inline static constexpr auto RTTI = RTTI_hkbStateMachine__EventPropertyArray;
			inline static constexpr auto VTABLE = VTABLE_hkbStateMachine__EventPropertyArray;

			EventPropertyArray() { stl::emplace_vtable(this); }

			// members
			hkArray<hkbEventProperty> events;  // 00
		};
		static_assert(sizeof(EventPropertyArray) == 0x20);

		class StateInfo : public hkbBindable
		{
		public:
			inline static constexpr auto RTTI = RTTI_hkbStateMachine__StateInfo;
			inline static constexpr auto VTABLE = VTABLE_hkbStateMachine__StateInfo;

			StateInfo();
			~StateInfo() override;  // 00

			// members
			hkArray<hkbStateListener*>    listeners;          // 30 -- A list of listeners that receive callbacks
			hkRefPtr<EventPropertyArray>  enterNotifyEvents;  // 40 -- These events are sent when the state is entered
			hkRefPtr<EventPropertyArray>  exitNotifyEvents;   // 48 -- These events are sent when the state is exited
			hkRefPtr<TransitionInfoArray> transitions;        // 50 -- The transitions out of this state
			hkRefPtr<hkbGenerator>        generator;          // 58 -- The generator associated with this state
			hkStringPtr                   name;               // 60 -- The name of this state
			uint32_t                      id;                 // 68
			/// 6C -- The state probability. When choosing a random start state, each state is weighted according to its probability.
			/// The probabilities of all of the states being considered are normalized so that their sum is 1.
			/// When choosing a random transition, each transition in weighted according to the probability of the to-state.
			float probability{ 1.0f };
			bool  enable{ true };  // 70 -- Enable this state. Otherwise, it will be inaccessible.
			char  pad71[7];        // 71
		};
		static_assert(sizeof(StateInfo) == 0x78);

		/// A time interval bounded by events or hkReals.
		///
		/// If you specify the interval using fixed times (hkReals), then the times correspond to
		/// the amount of local state machine time that has passed since the state was entered.
		/// If you specify the interval using events, then the interval begins whenever the
		/// m_enterEventId event is received and ends whenever the m_exitEventId is
		/// received.
		///
		/// An interval is bounded on both ends either by events or fixed times.  You can't use
		/// an event on one end and a fixed time on the other.
		///
		/// When using either interval specification, you should try to ensure that the interval
		/// is at least one frame long.  Otherwise, the interval may open and close again in one
		/// frame, and its effects may not be processed.
		///
		/// If either m_enterEventId or m_exitEventId are not EVENT_ID_NULL, then they define the interval.
		/// Otherwise (if both are EVENT_ID_NULL), the m_enterTime and m_exitTime will define the interval.
		struct TimeInterval
		{
			TimeInterval() :
				enterEventId(-1), exitEventId(-1), enterTime(0), exitTime(0) {}

			// members
			int32_t enterEventId;  // 00
			int32_t exitEventId;   // 04
			float   enterTime;     // 08
			float   exitTime;      // 0C
		};
		static_assert(sizeof(TimeInterval) == 0x10);

		struct TransitionInfo
		{
			enum class Flag : uint16_t
			{
				kNone = 0,
				FLAG_USE_TRIGGER_INTERVAL = 1 << 0,
				FLAG_USE_INITIATE_INTERVAL = 1 << 1,
				FLAG_UNINTERRUPTIBLE_WHILE_PLAYING = 1 << 2,
				FLAG_UNINTERRUPTIBLE_WHILE_DELAYED = 1 << 3,
				FLAG_DELAY_STATE_CHANGE = 1 << 4,
				FLAG_DISABLED = 1 << 5,
				FLAG_DISALLOW_RETURN_TO_PREVIOUS_STATE = 1 << 6,
				FLAG_DISALLOW_RANDOM_TRANSITION = 1 << 7,
				FLAG_DISABLE_CONDITION = 1 << 8,
				FLAG_ALLOW_SELF_TRANSITION_BY_TRANSITION_FROM_ANY_STATE = 1 << 9,
				FLAG_IS_GLOBAL_WILDCARD = 1 << 10,
				FLAG_IS_LOCAL_WILDCARD = 1 << 11,
				FLAG_FROM_NESTED_STATE_ID_IS_VALID = 1 << 12,
				FLAG_TO_NESTED_STATE_ID_IS_VALID = 1 << 13,
				FLAG_ABUT_AT_END_OF_FROM_GENERATOR = 1 << 14
			};
			using FLAGS = stl::enumeration<Flag, uint16_t>;

			TransitionInfo() = default;
			TransitionInfo(int32_t a_eventId, int32_t a_toStateId, hkbTransitionEffect* a_transition, hkbCondition* condition);

			// members

			/// 00 - The interval in which the event must be received for the transition to occur.
			///
			/// This is only used if (m_flags & FLAG_USE_TRIGGER_INTERVAL) is true.
			/// You should make sure that the interval is longer than your timestep
			/// (eg, 1/30 sec), or else the interval may be missed.
			TimeInterval triggerInterval;

			/// 10 - The interval in which the transition may begin.
			///
			/// This is only used if (m_flags & FLAG_USE_BEGIN_INTERVAL) is true.
			/// If the transition is activated outside of this interval, the transition
			/// will be delayed until the interval begins.
			/// You should make sure that the interval is longer than your timestep
			/// (eg, 1/30 sec), or else the interval may be missed.
			TimeInterval                  initiateInterval;
			hkRefPtr<hkbTransitionEffect> transition;         // 20
			hkRefPtr<hkbCondition>        condition;          // 28
			int32_t                       eventId;            // 30
			int32_t                       toStateId;          // 34
			int32_t                       fromNestedStateId;  // 38
			int32_t                       toNestedStateId;    // 3C
			uint16_t                      priority;           // 40
			FLAGS                         flags;              // 42
			uint32_t                      pad_44;             // 44
		};
		static_assert(sizeof(TransitionInfo) == 0x48);

		class TransitionInfoArray : public hkReferencedObject
		{
		public:
			inline static constexpr auto RTTI = RTTI_hkbStateMachine__TransitionInfoArray;
			inline static constexpr auto VTABLE = VTABLE_hkbStateMachine__TransitionInfoArray;

			TransitionInfoArray() { stl::emplace_vtable(this); }
			~TransitionInfoArray() override = default;  // 00

			// members
			hkArray<TransitionInfo> transitions;  // 10
		};
		static_assert(sizeof(TransitionInfoArray) == 0x20);

		/// A reference to a transition info within the state machine.  This indicates which list of transitions to use
		/// and what the index of the transition is in that list.
		struct TransitionInfoReference
		{
			TransitionInfoReference() = default;

			static const int16_t WILDCARD_STATE_INDEX = -1;
			static const int16_t SAME_STATE_MACHINE_ID = -1;

			/// Whether this references a transition or not.
			bool isValid() const { return m_transitionIndex >= 0; }

			// members
			int16_t m_fromStateIndex{ -2 };                     // 00 - The index of the state that the transition goes from, or -1 for a wildcard.
			int16_t m_transitionIndex{ WILDCARD_STATE_INDEX };  // 02 - The index of the transition in the list.
			int16_t m_stateMachineId{ SAME_STATE_MACHINE_ID };  // 04 - The id of the state machine from which this transition comes, or -1 if its from this state machine.
		};
		static_assert(sizeof(TransitionInfoReference) == 0x6);

		struct ActiveTransitionInfo
		{
			ActiveTransitionInfo() = default;
			~ActiveTransitionInfo() = default;

			// members
			hkbTransitionEffect*    effect;                                // 00
			hkRefVariant            mb_transitionEffectInternalStateInfo;  // 08
			TransitionInfoReference transitionInfoReference;               // 10 - A reference to the transition info.
			TransitionInfoReference transitionInfoReferenceForTE;          // 16 - A reference to the transition info where the TE came from (possibly different from the above). This is used to reconstruct the internal state.
			int32_t                 fromStateId;                           // 1C
			int32_t                 toStateId;                             // 20
			bool                    isReturnToPreviousState;               // 24
			char                    pad25[3];                              // 25
		};
		static_assert(sizeof(ActiveTransitionInfo) == 0x28);

		/// A transition that has been delayed and is waiting to initiate.
		struct DelayedTransitionInfo
		{
			// members
			char unk[24];
		};
		static_assert(sizeof(DelayedTransitionInfo) == 0x18);

		//hkbStateMachine() = default;
		~hkbStateMachine() override;  // 00

		// override (hkReferencedObject)
		const hkClass* GetClassType() const override;                                                                     // 01 - { return 0; }
		void           CalcContentStatistics(hkStatisticsCollector* a_collector, const hkClass* a_class) const override;  // 02

		// override (hkbBindable)
		void collectBindables(hkbBindableCollector& collector);  // 03

		// override (hkbNode)
		void                Activate(const hkbContext& a_context) override;                                                                                     // 04
		void                Update(const hkbContext& a_context, float a_timestep) override;                                                                     // 05
		void                handleEvent(const hkbContext& ctx, hkbEvent& event) override;                                                                       // 06
		void                Deactivate(const hkbContext& a_context) override;                                                                                   // 07
		int32_t             getMaxNumChildren(GET_CHILDREN_FLAGS flags);                                                                                        // 08
		void                getChildren(GET_CHILDREN_FLAGS flags, ChildrenInfo& ans) override;                                                                  // 09
		bool                isValid(hkStringPtr& err) const override;                                                                                           // 0A
		hkbNode*            cloneNode(hkbBehaviorGraph& rootBehavior) const override;                                                                           // 0C
		hkReferencedObject* createInternalState() override;                                                                                                     // 0D
		void                getInternalState(hkReferencedObject& internalState) const override;                                                                 // 0E
		void                getInternalStateUser(const hkbBehaviorGraph& rootBehavior, hkReferencedObject& internalState) const override;                       // 0F
		void                setInternalState(const hkReferencedObject& internalState) override;                                                                 // 10
		void                setInternalStateUser(const hkbContext& context, const hkReferencedObject& internalState, void* nodeIdToInternalStateMap) override;  // 11
		void                getActiveEvents(void* activeEvents) const override;                                                                                 // 12
		void                getActiveVariablesSpecial(void* activeVariables) const override;                                                                    // 14

		// override (hkbGenerator)
		void generate(const hkbContext& a_context, const hkbGeneratorOutput** activeChildrenOutput, hkbGeneratorOutput& output, float timeOffset = 0.0f) const override;  // 17
		bool canRecycleOutput() const override;                                                                                                                           // 18
		void updateSync(const hkbContext& a_context, hkbNodeInfo& info) override;                                                                                         // 19
		void startEcho() override;                                                                                                                                        // 1B

		/// Add a state given a state index, generator and name.
		///
		/// (not from the docs) If stateID is 0, adds new state to the start of the states array
		void addState(int32_t stateId, class hkbGenerator* generator, char const* name = nullptr);

		/// Add a state given a generator and name. returns the ID of the created state
		int32_t addState(hkbGenerator* generator, const char* name = nullptr);

		/// Add a transition and returns the newly created TransitionInfo.
		/// Note that the returned TransitionInfo is only valid until you
		/// call addTransition() again, because each call to addTransition()
		/// may reallocate the internal array of TransitionInfos.
		///
		/// \param eventId The ID of the event that triggers the transition.
		/// \param fromState The state from which this transition occurs.
		/// \param toState The state to which this transition goes.
		/// \param transition The transition to apply.
		/// \param condition The condition that must be true for the transition to occur.
		TransitionInfo* addTransition(int32_t eventId, int32_t fromStateId,
			int32_t toStateId, hkbTransitionEffect* transition = nullptr, hkbCondition* condition = nullptr);

		/// add the transition
		TransitionInfo* addTransitionInternal(int32_t eventId, int32_t toStateId, hkbTransitionEffect* transition, hkbCondition* condition, hkArray<TransitionInfo>& transitions);

		uint16_t getCurrentStateIndex() const;

		hkbStateMachine* getNestedStateMachineClone(const hkbBehaviorGraph& behaviorGraph, int32_t stateIndex);

		hkbBehaviorGraph::StateMachineInfo* getNestedStateMachineInfo(const hkbBehaviorGraph& behaviorGraph, int32_t stateIndex);

		/// get the nested state machine template given the nested state machine index
		hkbStateMachine* getNestedStateMachineTemplate(const hkbBehaviorGraph& behaviorGraph, int32_t stateIndex);

		/// Get a state index given the state ID.
		int32_t getStateIndex(int32_t stateID) const;

		/// Get the StateInfo for a state given the id.
		StateInfo& getStateInfoById(int32_t stateId);

		/// Get the StateInfo (const) for a state given the id.
		const StateInfo& getStateInfoById(int32_t stateId) const;

		/// Get the StateInfo for a state given the index (in the range of 0 to getNumStates()-1).
		StateInfo& getStateInfoByIndex(int32_t stateIndex);

		/// Get the StateInfo (const) for a state given the index (in the range of 0 to getNumStates()-1).
		const StateInfo& getStateInfoByIndex(int32_t stateIndex) const;

		/// Return a state ID that has not been used yet (the smallest positive ID).
		///
		/// This method requires time linear in the number of states, so use it sparingly.
		/// It's better to choose the IDs yourself.
		int32_t getUnusedStateId() const;

		// members
		hkbEvent                                                       eventToSendWhenStateOrTransitionChanges;                               // 048 - If non-null, this event is sent at the beginning and end of a transition, or once for an instantaneous transition.
		hkRefPtr<hkbStateChooser>                                      startStateChooser;                                                     // 060 - An object that chooses the start state
		std::int32_t                                                   startStateID{ 0 };                                                     // 068
		std::int32_t                                                   returnToPreviousStateEventID{ -1 };                                    // 06C - If this event is received, the state machine returns to the previous state if there is an appropriate transition defined.
		std::int32_t                                                   randomTransitionEventID{ -1 };                                         // 070 - If this event is received, the state machine chooses a random transition from among those available.
		std::int32_t                                                   transitionToNextHigherStateEventID{ -1 };                              // 074 - If the event is received, the state machine chooses a state with the id higher than the m_currentStateId and do a transition to that state.
		std::int32_t                                                   transitionToNextLowerStateEventID{ -1 };                               // 078 - If the event is received, the state machine chooses a state with the id lower than the m_currentStateId and do a transition to that state.
		std::int32_t                                                   syncVariableIndex{ -1 };                                               // 07C - We use variables to sync the start state of the state machine.
		std::int32_t                                                   currentStateID{ 0 };                                                   // 080
		bool                                                           wrapAroundStateID{ true };                                             // 084
		std::int8_t                                                    maxSimultaneousTransitions{ 32 };                                      // 085 - The number of transitions that can be active at once.
		stl::enumeration<StartStateMode, std::uint8_t>                 startStateMode{ StartStateMode ::kDefault };                           // 086 - How to set the start state.
		stl::enumeration<StateMachineSelfTransitionMode, std::uint8_t> selfTransitionMode{ StateMachineSelfTransitionMode ::kNoTransition };  // 087 - How to deal with self-transitions (when the state machine is transitioned to while still active).
		bool                                                           isActive{ false };                                                     // 088 - Whether or not the state machine is active (activate() called but not deactivate()).
		char                                                           pad89[7];                                                              // 089
		hkArray<StateInfo*>                                            states;                                                                // 090 - The list of states
		hkRefPtr<TransitionInfoArray>                                  wildcardTransitions;                                                   // 0A0 - The list of transitions from any state (don't have a specific from state)
		hkScopedPtr<hkPointerMap<int64_t, int64_t>>                    stateIDToIndexMap;                                                     // 0A8 - State id to index map
		hkArray<ActiveTransitionInfo>                                  activeTransitions;                                                     // 0B0 - The list of currently active transitions
		hkArray<uint8_t>                                               transitionFlags;                                                       // 0C0 - Internal flags for the transitions of the current state
		hkArray<uint8_t>                                               wildcardTransitionFlags;                                               // 0D0 - Internal flags for the wildcard transitions
		hkArray<DelayedTransitionInfo>                                 delayedTransitions;                                                    // 0E0 - This list consists of all transitions which have their initiate intervals flag or their abutment flag set.
		float                                                          timeInState{ 0 };                                                      // 0F0 - How many seconds we've been in the current state
		float                                                          lastLocalTime{ 0 };                                                    // 0F4 - What was the last local time from the syncInfo
		std::int32_t                                                   previousStateID{ 0 };                                                  // 0F8
		std::int32_t                                                   nextStartStateIndexOverride{ -1 };                                     // 0FC - The index of the next start state if overridden (-1 means not overridden)
		bool                                                           stateOrTransitionChanged{ false };                                     // 100 - Whether the state or transition has changed lately
		bool                                                           echoNextUpdate{ false };                                               // 101 - Whether or not to perform an echo next time update() is called.
		std::uint16_t                                                  currentStateIndexAndEntered{ 0 };                                      // 102
		std::uint32_t                                                  pad0BC;                                                                // 104
	};
	static_assert(sizeof(hkbStateMachine) == 0x108);
}
