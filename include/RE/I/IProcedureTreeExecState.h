
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
	    virtual void           Cleanup(void* a_context);                                // 01 - nullsub
	    virtual void           RecycleChildren() = 0;                                   // 02 - _purecall
	    virtual void*          GetDialogueTopicSelection();                             // 03 - { return ...; }
	    virtual void*          GetHoldPositionLocation();                               // 04 - { return ...; }
	    virtual BSFixedString* QType() = 0;                                             // 05 - _purecall
	    virtual void           SaveGame(BGSSaveFormBuffer* a_buf, void* a_customData);  // 06 - nullsub
	    virtual void           LoadGame(BGSLoadFormBuffer* a_buf, void* a_customData);  // 07 - nullsub
	    virtual void           InitLoadGame(BGSLoadFormBuffer* a_buf);                  // 08 - nullsub
	};
	static_assert(sizeof(IProcedureTreeExecState) == 0x8);
}
