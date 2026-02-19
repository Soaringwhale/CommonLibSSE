#pragma once

#include "RE/B/BSAudioManagerThread.h"
#include "RE/B/BSFixedString.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/BSXAudio2GameSound.h"

namespace RE
{
	class BSISoundDescriptor;
	class SoundMessageStack;
	struct BSSoundHandle;

	struct BSSoundInfo
	{
		//members
		std::uint32_t     soundID;       // 00
		std::uint32_t     flags;         // 04
		void*             soundOrState;  // 08
		BSSoundInfo*      nextInBucket;  // 10
		std::uint32_t     unk14;         // 18
		std::uint8_t      someState;     // 1C
		std::uint8_t      pad1D[3];      // 1D
		std::uint32_t     pad20;         // 20
	};
	static_assert(sizeof(BSSoundInfo) == 0x28);

	class BSAudioManager
	{
	public:
		static BSAudioManager* GetSingleton();

		bool Play(FormID a_soundFormID);
		bool Play(BSISoundDescriptor* a_descriptor);
		bool BuildSoundDataFromDescriptor(BSSoundHandle& a_soundHandle, BSISoundDescriptor* a_descriptor, std::uint32_t a_flags = 0x1A);
		void BuildSoundDataFromEditorID(BSSoundHandle& a_soundHandle, const char* a_editorID, std::uint32_t a_flags);

		// members
		std::int32_t                                  listInd;                // 000
		std::int32_t                                  unk4;                   // 004
		SoundMessageList*                             lists[2];               // 008
		SoundMessageStack*                            stack1;                 // 018
		SoundMessageStack*                            stack2;                 // 020
		BSTHashMap<std::uint32_t, BSGameSound*>       soundMap;               // 028
		BSTHashMap<std::uint32_t, BSSoundInfo*>       soundStateMap;          // 058
		BSTHashMap<std::uint32_t, NiAVObject*>        movingRefrMap;          // 088  // std::uint32_t, NiAVObject*>
		BSTHashMap<NiAVObject*, BSISoundOutputModel*> objectOutputOverrides;  // 0B8
		std::int64_t                                  cashe_sounds_bstlist;   // 0E8
		std::int32_t                                  unkF0;                  // 0F0
		std::int32_t                                  treadID;                // 0F4
		BSAudioManagerThread*                         thread;                 // 0F8
		std::int32_t                                  unk100;                 // 100
		std::int32_t                                  unk104;                 // 104
		BSFixedString                                 unk108;                 // 108
		std::uint64_t                                 unk110;                 // 110
		char                                          unk118;                 // 118
		char                                          unk119;                 // 119
		char                                          unk11A[2];              // 11A
		std::int32_t                                  unk11C;                 // 11C
		std::uint64_t                                 unk120;                 // 120
		std::int32_t                                  unk128;                 // 128
		std::int32_t                                  unk12C;                 // 12C
		std::int32_t                                  unk130;                 // 130
		std::int32_t                                  unk134;                 // 134
		std::uint64_t                                 unk138;                 // 138
		BSFixedString                                 unk140;                 // 140
		std::uint64_t                                 unk148;                 // 148
		std::uint64_t                                 unk150;                 // 150
		std::uint64_t                                 unk158;                 // 158
		std::int32_t                                  audioCacheSize;         // 160
		std::int32_t                                  max_AudioCacheSize;     // 164
		std::int32_t                                  unk168;                 // 168
		std::uint32_t                                 flags;                  // 16C
		std::int32_t                                  unk170;                 // 170
		std::uint32_t                                 unk174;                 // 174
		std::uint64_t                                 unk178;                 // 178
		std::uint64_t                                 unk180;                 // 180
		std::uint64_t                                 unk188;                 // 188
	};
	static_assert(sizeof(BSAudioManager) == 0x190);
}
