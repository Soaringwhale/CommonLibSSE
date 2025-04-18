#include "RE/H/hkbBlendingTransitionEffect.h"

#include "RE/H/hkContainerAllocators.h"
#include "RE/H/hkaSkeleton.h"
#include "RE/H/hkbBehaviorGraph.h"
#include "RE/H/hkbCharacterSetup.h"
#include "RE/H/hkbNodeInfo.h"
#include "RE/H/hkbProjectData.h"
#include "RE/H/hkbUtils.h"

namespace RE
{
	namespace hkbBlendingTransitionEffectUtils
	{
		void generateInternal(const hkbBlendingTransitionEffect& effect, float timeOffset, hkQsTransform* pose, const hkbGeneratorOutput** activeChildrenOutput, hkbGeneratorOutput& output)
		{
			using func_t = decltype(generateInternal);
			REL::Relocation<func_t> func{ RELOCATION_ID(59402, 0) };
			return func(effect, timeOffset, pose, activeChildrenOutput, output);
		}
	}

	hkbBlendingTransitionEffect::hkbBlendingTransitionEffect(float a_duration, Flags a_flags, EndMode a_endMode) :
		duration(a_duration), flags(a_flags), endMode(a_endMode)
	{
		stl::emplace_vtable(this);
	}

	void hkbBlendingTransitionEffect::Activate(const hkbContext& ctx)
	{
		if (timeRemaining < std::numeric_limits<float>::epsilon()) {
			timeRemaining = duration;
			timeInTransition = 0;
			applySelfTransition = computeSelfTransitionMode(ctx, toGenerator);
		}
		defaultEventMode = ctx.character->projectData->defaultEventMode;
	}

	void hkbBlendingTransitionEffect::Update(const hkbContext& a_context, float a_timestep)
	{
		update(a_context, a_timestep, this);
	}

	void hkbBlendingTransitionEffect::Deactivate(const hkbContext&)
	{
		timeRemaining = 0;
		characterPoseAtBeginningOfTransition.clear();
		initializeCharacterPose = false;
	}

	void hkbBlendingTransitionEffect::getChildren(GET_CHILDREN_FLAGS a_flags, ChildrenInfo& ans)
	{
		if (!a_flags.all(GET_CHILDREN_FLAG::kActiveOnly))
			return;

		if (applySelfTransition && selfTransitionMode == SelfTransitionMode::SELF_TRANSITION_MODE_RESET) {
			ans.reset = true;
			applySelfTransition = false;
		}

		ans.childInfos.push_back({});
		ans.childInfos[0].node = toGenerator;
		ans.childInfos[0].reset = ans.reset;

		if (fromGenerator != toGenerator) {
			ans.childInfos.push_back({});
			ans.childInfos[1].node = fromGenerator;
			ans.childInfos[1].reset = false;

			if (a_flags.all(GET_CHILDREN_FLAG::kGeneratorsOnly)) {
				ans.childInfos[0].syncToParent = 1;
				ans.childInfos[1].syncToParent = 1;
				ans.syncToParent = 1;
			}
		}

		if (auto emode = getEventMode(); emode == EventMode::EVENT_MODE_IGNORE_FROM_GENERATOR || emode == EventMode::EVENT_MODE_IGNORE_TO_GENERATOR) {
			ans.ignoreEvents = true;
			if (fromGenerator == toGenerator) {
				ans.childInfos[0].ignoreEvents = false;
			} else {
				ans.childInfos[0].ignoreEvents = emode == EventMode::EVENT_MODE_IGNORE_TO_GENERATOR;
				ans.childInfos[1].ignoreEvents = emode == EventMode::EVENT_MODE_IGNORE_FROM_GENERATOR;
			}
		}
	}

	void hkbBlendingTransitionEffect::getInternalState(hkReferencedObject& internalState) const
	{
		auto& ans = static_cast<hkbBlendingTransitionEffectInternalState&>(internalState);

		ans.characterPoseAtBeginningOfTransition.append(characterPoseAtBeginningOfTransition);
		ans.timeRemaining = timeRemaining;
		ans.timeInTransition = timeInTransition;
		ans.applySelfTransition = applySelfTransition;
		ans.initializeCharacterPose = initializeCharacterPose;
	}

	void hkbBlendingTransitionEffect::setInternalState(const hkReferencedObject& internalState)
	{
		auto& state = static_cast<const hkbBlendingTransitionEffectInternalState&>(internalState);

		characterPoseAtBeginningOfTransition.append(state.characterPoseAtBeginningOfTransition);
		timeRemaining = state.timeRemaining;
		timeInTransition = state.timeInTransition;
		applySelfTransition = state.applySelfTransition;
		initializeCharacterPose = state.initializeCharacterPose;
	}

	hkbBlendingTransitionEffect::hkbBlendingTransitionEffect(const hkbBlendingTransitionEffect& other) :
		duration(other.duration), toGeneratorStartTimeFraction(other.toGeneratorStartTimeFraction), flags(other.flags), endMode(other.endMode), blendCurve(other.blendCurve)
	{
		stl::emplace_vtable(this);
	}

	void hkbBlendingTransitionEffect::generate(const hkbContext& a_context, const hkbGeneratorOutput** activeChildrenOutput, hkbGeneratorOutput& output, float timeOffset) const
	{
		auto poseLocal = a_context.character->getPoseLocal();
		hkbBlendingTransitionEffectUtils::generateInternal(*this, timeOffset, poseLocal, activeChildrenOutput, output);
	}

	void hkbBlendingTransitionEffect::updateSync(const hkbContext& a_context, hkbNodeInfo&)
	{
		updateSync(a_context, this);
	}

	bool hkbBlendingTransitionEffect::isDone()
	{
		return timeInTransition > 0.0f && (fromGenerator == toGenerator || timeRemaining <= 0.0f);
	}

	bool hkbBlendingTransitionEffect::isSyncable(hkbBehaviorGraph& behaviorGraph)
	{
		return getFromGeneratorSyncInfo(behaviorGraph).duration != 0 || getToGeneratorSyncInfo(behaviorGraph).duration != 0;
	}

	const hkbGeneratorSyncInfo& hkbBlendingTransitionEffect::getFromGeneratorSyncInfo(hkbBehaviorGraph& behaviorGraph)
	{
		auto& fromGeneratorInfo = behaviorGraph.getNodeInfoByClone(fromGenerator);
		return behaviorGraph.adjust_info_usesomeind(fromGeneratorInfo).syncInfo;
	}
	
	const hkbGeneratorSyncInfo& hkbBlendingTransitionEffect::getToGeneratorSyncInfo(hkbBehaviorGraph& behaviorGraph)
	{
		auto& toGeneratorInfo = behaviorGraph.getNodeInfoByClone(toGenerator);
		return behaviorGraph.adjust_info_usesomeind(toGeneratorInfo).syncInfo;
	}

	void hkbBlendingTransitionEffect::update(const hkbContext& ctx, float dtime, hkbGenerator* generator)
	{
		auto& _generator_info = hkbUtils::get_active_info(ctx, generator);
		auto& generator_info = hkbUtils::adjust_info_usesomeind(ctx, _generator_info);

		float dur = generator_info.syncInfo.duration;
		float freq = dur != 0.0f ? 1.0f / dur : 0.0f;
		float new_local_time = generator_info.syncInfo.localTime + dtime;
		generator_info.syncInfo.localTime = new_local_time;

		if (dur != 0.0f && new_local_time > freq)
			generator_info.syncInfo.localTime = new_local_time - static_cast<int32_t>(new_local_time / freq) * freq;

		bool not_initializeCharacterPose = !initializeCharacterPose;
		timeInTransition += dtime;
		timeRemaining -= dtime;

		if (!not_initializeCharacterPose && characterPoseAtBeginningOfTransition.empty()) {
			int32_t bones_count = ctx.character->setup->animationSkeleton->bones.size();
			characterPoseAtBeginningOfTransition.reserve(bones_count);

			auto poseLocal = ctx.character->getPoseLocal();
			characterPoseAtBeginningOfTransition.append(poseLocal, bones_count);
		}
	}
	
	void hkbBlendingTransitionEffect::updateSync(const hkbContext& ctx, hkbGenerator* gen)
	{
		using func_t = void (hkbBlendingTransitionEffect*, const hkbContext& ctx, hkbGenerator* gen);
		REL::Relocation<func_t> func{ RELOCATION_ID(59289, 0) };
		return func(this, ctx, gen);
	}
}
