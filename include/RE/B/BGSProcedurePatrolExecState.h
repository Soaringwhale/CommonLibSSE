
#pragma once

#include "RE/I/IProcedureTreeExecState.h"

namespace RE
{
	class PatrolActorPackageData;
	class PackageTarget;
	class BSPathingRequest;

	class BGSProcedurePatrolExecState : public IProcedureTreeExecState
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSProcedurePatrolExecState;

		~BGSProcedurePatrolExecState() override;                                             // 00

		// override (IProcedureTreeExecState)
		void               Cleanup(void* a_context) override;                                // 01
		void               RecycleChildren() override;                                       // 02
		BSFixedString*     QType() override;                                                 // 05
		void               SaveGame(BGSSaveFormBuffer* a_buf, void* a_customData) override;  // 06
		void               LoadGame(BGSLoadFormBuffer* a_buf, void* a_customData) override;  // 07
		void               InitLoadGame(BGSLoadFormBuffer* a_buf) override;                  // 08

		// members
		float                   patrolRadius;            // 08
		std::uint32_t           pad0C;                   // 0C
		PatrolActorPackageData* patrolPackageData;       // 10
		void*                   idleMarkerState;         // 18
		void*                   sitSleepExecState;       // 20
		BGSPackageDataRef       externalTargetData;      // 28
		BSPathingRequest*       currentPathingRequest;   // 48
		bool                    unk50;                   // 50
		bool                    bAtRef;                  // 51
		bool                    bFlightStateFlag;        // 52
		char                    unk53[5];                // 53
	};
	static_assert(sizeof(BGSProcedurePatrolExecState) == 0x58);
}
