
#pragma once

namespace RE
{
	class BGSSaveFormBuffer;
	class BGSLoadFormBuffer;

	class IProcedureTreeExecState
	{
	public:
	    inline static constexpr auto RTTI = RTTI_IProcedureTreeExecState;
	
	    virtual ~IProcedureTreeExecState();                                             // 00
	
	    // add
	    virtual void                 Cleanup(void* a_context);                                // 01 - { return; }
	    virtual void                 RecycleChildren() = 0;                                   // 02
	    virtual void*                GetDialogueTopicSelection();                             // 03 - { return 0; }
	    virtual void*                GetHoldPositionLocation();                               // 04 - { return 0; }
	    virtual const BSFixedString& QType() = 0;                                             // 05
	    virtual void                 SaveGame(BGSSaveFormBuffer* a_buf, void* a_customData);  // 06 - { return; }
	    virtual void                 LoadGame(BGSLoadFormBuffer* a_buf, void* a_customData);  // 07 - { return; }
	    virtual void                 InitLoadGame(BGSLoadFormBuffer* a_buf);                  // 08 - { return; }
	};
	static_assert(sizeof(IProcedureTreeExecState) == 0x8);
}
