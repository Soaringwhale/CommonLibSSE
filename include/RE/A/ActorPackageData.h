
#pragma once

namespace RE
{
	class IProcedureTreeExecState;
	class BGSSaveFormBuffer;
	class BGSLoadFormBuffer;
	class TESPackage;
	
	class ActorPackageData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ActorPackageData;
		
		virtual ~ActorPackageData();                                                              // 00
		
		// add
		virtual std::uint32_t            GetPackageType() = 0;                                    // 01 - purecall
		virtual IProcedureTreeExecState* GetProcedureExecState();                                 // 02 - { return nullptr; }
		virtual void                     SetProcedureExecState(IProcedureTreeExecState* a_state); // 03 - { return; }
		virtual void                     ClearProcedureExecState();                               // 04 - { return; }
		virtual void                     SaveGame(BGSSaveFormBuffer* a_buf) = 0;                  // 05 - purecall
		virtual void                     LoadGame(BGSLoadFormBuffer* a_buf) = 0;                  // 06 - purecall
		virtual void                     InitLoadGame(BGSLoadFormBuffer* a_buf);                  // 07 - nullsub
		virtual void                     ResetPackData(TESPackage* a_package);                    // 08 - { return; }
	};
	static_assert(sizeof(ActorPackageData) == 0x8);
}
