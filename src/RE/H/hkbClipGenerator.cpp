#include "RE/H/hkbClipGenerator.h"

namespace RE
{
	void RE::hkbClipGenerator::addTrigger(float atLocalTime, const hkbEventBase& event, bool relativeToEndOfClip, bool acyclic, bool isAnnotation)
	{
		REL::Relocation<decltype(&hkbClipGenerator::addTrigger)> func(RELOCATION_ID(58614, 0));
		return func(this, atLocalTime, event, relativeToEndOfClip, acyclic, isAnnotation);
	}
	float RE::hkbClipGenerator::getDurationLocalTime() const
	{
		auto  animation = animationControl->binding ? animationControl->binding->animation.get() : nullptr;
		float duration = animation ? animation->duration : 0.01333f;
		return fmaxf(duration - (animationControl->cropEndAmountLocalTime + animationControl->cropStartAmountLocalTime), 0.0f);
	}
	const hkClass& hkbClipGenerator::staticClass()
	{
		return *REL::Relocation<hkClass*>(REL::ID(521225));
	}
	hkbClipGenerator::hkbClipGenerator()
	{
		stl::emplace_vtable(this);
	}
	const hkClass* hkbClipGenerator::GetClassType() const
	{
		return &hkbClipGenerator::staticClass();
	}
	void hkbClipGenerator::CalcContentStatistics(hkStatisticsCollector* a_collector, const hkClass* a_class) const
	{
		using func_t = decltype(&hkbClipGenerator::CalcContentStatistics);
		REL::Relocation<func_t> func{ RELOCATION_ID(58611, 0) };
		return func(this, a_collector, a_class);
	}
	void hkbClipGenerator::Activate(const hkbContext& a_context)
	{
		using func_t = decltype(&hkbClipGenerator::Activate);
		REL::Relocation<func_t> func{ RELOCATION_ID(58602, 0) };
		return func(this, a_context);
	}
	void hkbClipGenerator::Update(const hkbContext& a_context, float a_timestep)
	{
		using func_t = decltype(&hkbClipGenerator::Update);
		REL::Relocation<func_t> func{ RELOCATION_ID(58603, 0) };
		return func(this, a_context, a_timestep);
	}
	void hkbClipGenerator::Deactivate(const hkbContext& a_context)
	{
		using func_t = decltype(&hkbClipGenerator::Deactivate);
		REL::Relocation<func_t> func{ RELOCATION_ID(58604, 0) };
		return func(this, a_context);
	}
	bool hkbClipGenerator::isValid(hkStringPtr& err) const
	{
		using func_t = decltype(&hkbClipGenerator::isValid);
		REL::Relocation<func_t> func{ RELOCATION_ID(58605, 0) };
		return func(this, err);
	}
	hkbNode* hkbClipGenerator::cloneNode(hkbBehaviorGraph& rootBehavior) const
	{
		using func_t = decltype(&hkbClipGenerator::cloneNode);
		REL::Relocation<func_t> func{ RELOCATION_ID(58606, 0) };
		return func(this, rootBehavior);
	}
	hkReferencedObject* hkbClipGenerator::createInternalState()
	{
		using func_t = decltype(&hkbClipGenerator::createInternalState);
		REL::Relocation<func_t> func{ RELOCATION_ID(59329, 0) };
		return func(this);
	}
	void hkbClipGenerator::getInternalState(hkReferencedObject& internalState) const
	{
		using func_t = decltype(&hkbClipGenerator::getInternalState);
		REL::Relocation<func_t> func{ RELOCATION_ID(59330, 0) };
		return func(this, internalState);
	}
	void hkbClipGenerator::setInternalState(const hkReferencedObject& internalState)
	{
		using func_t = decltype(&hkbClipGenerator::setInternalState);
		REL::Relocation<func_t> func{ RELOCATION_ID(59331, 0) };
		return func(this, internalState);
	}
	void hkbClipGenerator::generate(const hkbContext& a_context, const hkbGeneratorOutput** activeChildrenOutput, hkbGeneratorOutput& output, float timeOffset) const
	{
		using func_t = decltype(&hkbClipGenerator::generate);
		REL::Relocation<func_t> func{ RELOCATION_ID(58607, 0) };
		return func(this, a_context, activeChildrenOutput, output, timeOffset);
	}
	void hkbClipGenerator::updateSync(const hkbContext& a_context, hkbNodeInfo& info)
	{
		using func_t = decltype(&hkbClipGenerator::updateSync);
		REL::Relocation<func_t> func{ RELOCATION_ID(58608, 0) };
		return func(this, a_context, info);
	}
	void hkbClipGenerator::setLocalTime(float a_time)
	{
		using func_t = decltype(&hkbClipGenerator::setLocalTime);
		REL::Relocation<func_t> func{ RELOCATION_ID(58609, 0) };
		return func(this, a_time);
	}
	void hkbClipGenerator::startEcho()
	{
		using func_t = decltype(&hkbClipGenerator::startEcho);
		REL::Relocation<func_t> func{ RELOCATION_ID(58610, 0) };
		return func(this);
	}
}
