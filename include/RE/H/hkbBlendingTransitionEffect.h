#pragma once

#include "RE/H/hkQsTransform.h"
#include "RE/H/hkbTransitionEffect.h"

namespace RE
{
	class hkbGeneratorSyncInfo;

	class hkbBlendingTransitionEffectInternalState : public hkReferencedObject
	{
	public:
		hkbBlendingTransitionEffectInternalState() { stl::emplace_vtable(this); }
		~hkbBlendingTransitionEffectInternalState() = default;

		// members
		hkArray<hkQsTransform> characterPoseAtBeginningOfTransition;  // 10
		float                  timeRemaining;                         // 20
		float                  timeInTransition;                      // 24
		bool                   applySelfTransition;                   // 28
		bool                   initializeCharacterPose;               // 29
		char                   pad2A[6];
	};
	static_assert(sizeof(hkbBlendingTransitionEffectInternalState));

	class hkbBlendingTransitionEffect : public hkbTransitionEffect
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbBlendingTransitionEffect;
		inline static constexpr auto VTABLE = VTABLE_hkbBlendingTransitionEffect;

		static const hkClass& staticClass()
		{
			return *REL::Relocation<hkClass*>(REL::ID(521850));
		}

		/// Flags to indicate specialized behavior.
		enum class FlagBits : uint16_t
		{
			/// No flags.
			FLAG_NONE = 0x0,

			/// Just use the worldFromModel of the generator being transitioned to.
			FLAG_IGNORE_FROM_WORLD_FROM_MODEL = 0x1,

			/// Synchronize the cycles of the children.
			FLAG_SYNC = 0x2,

			/// Just use the worldFromModel of the generator being transitioned from.
			FLAG_IGNORE_TO_WORLD_FROM_MODEL = 0x4,

			/// Blend the to and from world from models but ignore the to generator's rotation
			FLAG_IGNORE_TO_WORLD_FROM_MODEL_ROTATION = 0x8,
		};
		using Flags = stl::enumeration<FlagBits, uint16_t>;

		/// Modes regarding how to deal with the end of the "from" generator.
		enum class EndMode : uint8_t
		{
			/// Don't do anything special regarding the end of the "from" generator.
			END_MODE_NONE = 0,

			/// Ignore m_duration, and instead transition until the end of the "from" generator.
			END_MODE_TRANSITION_UNTIL_END_OF_FROM_GENERATOR = 1,

			/// If the transition begins closer than m_duration to the end of the "from" generator,
			/// shorten the transition duration to the time remaining so that the transition does
			/// not play the "from" generator beyond the end.
			END_MODE_CAP_DURATION_AT_END_OF_FROM_GENERATOR = 2,
		};

		hkbBlendingTransitionEffect() { stl::emplace_vtable(this); }
		hkbBlendingTransitionEffect(float a_duration, Flags flags = FlagBits::FLAG_NONE, EndMode endMode = EndMode::END_MODE_NONE);
		~hkbBlendingTransitionEffect() = default;

		// override (hkReferencedObject)
		const hkClass* GetClassType() const override { return &staticClass(); }  // 01

		// override (hkbNode)
		void                Activate(const hkbContext& a_context) override;                                                                               // 04
		void                Update(const hkbContext& a_context, float a_timestep) override;                                                               // 05
		void                Deactivate(const hkbContext& a_context) override;                                                                             // 07
		void                getChildren(GET_CHILDREN_FLAGS flags, ChildrenInfo& ans) override;                                                            // 09
		hkbNode*            cloneNode([[maybe_unused]] hkbBehaviorGraph& rootBehavior) const override { return new hkbBlendingTransitionEffect(*this); }  // 0C
		hkReferencedObject* createInternalState() override { return new hkbBlendingTransitionEffectInternalState(); }                                     // 0D
		void                getInternalState(hkReferencedObject& internalState) const override;                                                           // 0E
		void                setInternalState(const hkReferencedObject& internalState) override;                                                           // 10

		// override (hkbGenerator)
		void generate(const hkbContext& a_context, const hkbGeneratorOutput** activeChildrenOutput, hkbGeneratorOutput& output, float timeOffset = 0.0f) const override;  // 17
		bool canRecycleOutput() const override { return fromGenerator == toGenerator; }                                                                                   // 18
		void updateSync(const hkbContext& a_context, hkbNodeInfo& info) override;                                                                                         // 19

		// override (hkbTransitionEffect)
		bool  isDone() override;                                                             // 1C
		void  setFromGenerator(hkbGenerator* fromGen) override { fromGenerator = fromGen; }  // 1D
		void  setToGenerator(hkbGenerator* toGen) override { toGenerator = toGen; }          // 1E
		float getFromGeneratorBlendOutTime() override { return duration; }                   // 1F
		float getToGeneratorBlendInTime() override { return duration; }                      // 20

		// add
		virtual bool                        isSyncable(hkbBehaviorGraph& behaviorGraph);                                      // 21
		virtual bool                        hasToGeneratorBeenActivatedInThisFrame() const { return timeInTransition == 0; }  // 22
		virtual bool                        useFromGeneratorToSyncOnly() const { return false; };                             // 23
		virtual const hkbGeneratorSyncInfo& getFromGeneratorSyncInfo(hkbBehaviorGraph& behaviorGraph);                        // 24
		virtual float                       getTransitionDuration() const { return duration; }                                // 25
		virtual bool                        isFirstFrame() const { return hasToGeneratorBeenActivatedInThisFrame(); }         // 26

		const hkbGeneratorSyncInfo& getToGeneratorSyncInfo(hkbBehaviorGraph& behaviorGraph);
		void                        update(const hkbContext& ctx, float dtime, hkbGenerator* generator);
		void                        updateSync(const hkbContext& ctx, hkbGenerator* gen);

		// members
		float                  duration{ 0.0f };                      // 50
		float                  toGeneratorStartTimeFraction{ 0.0f };  // 54 - The start time of the to-generator when the transition begins, expressed as a fraction of its duration.
		Flags                  flags{};                               // 58 - Flags to indicate specialized behavior.
		EndMode                endMode{ EndMode ::END_MODE_NONE };    // 5A - The treatment of the end of the from-generator.
		uint8_t                blendCurve{ 0 };                       // 5B
		char                   pad5C[4];                              // 5C
		hkbGenerator*          fromGenerator{ nullptr };              // 60
		hkbGenerator*          toGenerator{ nullptr };                // 68
		hkArray<hkQsTransform> characterPoseAtBeginningOfTransition;  // 70
		float                  timeRemaining{ 0.0f };                 // 80
		float                  timeInTransition{ 0.0f };              // 84
		bool                   applySelfTransition{ false };          // 88
		bool                   initializeCharacterPose{ false };      // 89
		char                   field_8A[6];                           // 8A

	protected:
		hkbBlendingTransitionEffect(const hkbBlendingTransitionEffect& other);
	};
	static_assert(sizeof(hkbBlendingTransitionEffect) == 0x90);
}
