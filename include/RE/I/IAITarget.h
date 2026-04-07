
#pragma once

namespace RE
{ 
	class AITargetContext;

    class IAITarget : 
		public IAIWorldLocationHandle, // 00
		public IPackageData            // 08
	{
	public:
		inline static constexpr auto RTTI = RTTI_IAITarget;

		~IAITarget() override; // 00

		virtual void*         GetRefOrContainer(AITargetContext& a_context);                         // 04
		virtual void*         GetObjectA(AITargetContext& a_context);                                // 05
		virtual std::uint32_t GetAcquireType();                                                      // 06
		virtual bool          IsValidTarget(AITargetContext& a_context, const TESObjectREFR* a_ref); // 07
		virtual bool          GetHasFurtherTargets();                                                // 08
		virtual void          AdvanceToNextTarget();                                                 // 09
		virtual std::uint32_t GetCount();                                                            // 0A
		virtual void*         GetIterInterface();                                                    // 0B
	};
	static_assert(sizeof(IAITarget) == 0x10);
}
