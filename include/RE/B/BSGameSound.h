#pragma once

#include "RE/I/ID.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class NiAVObject;
	class BSISoundCategory;
	class BSISoundOutputModel;

	enum SOUND_MSG : std::int32_t
	{
		SOUND_MSG_StopAudioThread = 0x2,
		SOUND_MSG_Play = 0x4,
		SOUND_MSG_Pause = 0x5,
		SOUND_MSG_Unpause = 0x6,
		SOUND_MSG_Stop = 0x7,
		SOUND_MSG_PlayAfter = 0x8,
		SOUND_MSG_SetVolume = 0xD,
		SOUND_MSG_SetMinFrequence = 0xE,
		SOUND_MSG_SetFrequenceSpread = 0xF,
		SOUND_MSG_FadeTo = 0x12,
		SOUND_MSG_SetPosition = 0x13,
		SOUND_MSG_SetBeamEnd = 0x14,
		SOUND_MSG_SetStaticAttenuation = 0x15,
		SOUND_MSG_Release = 0x1A,
		SOUND_MSG_KillAll = 0x1B,
		SOUND_MSG_SetObjectToFollow = 0x1D,
		SOUND_MSG_ClearFollowedObject = 0x1E,
		SOUND_MSG_StopMovingSounds = 0x1F,
		SOUND_MSG_FollowedObjectSwap = 0x20,
		SOUND_MSG_SuspendAudioThread = 0x27,
		SOUND_MSG_PositionListener = 0x28,
		SOUND_MSG_OrientListener1 = 0x29,
		SOUND_MSG_OrientListener2 = 0x2A,
		SOUND_MSG_SetCompletionCallback = 0x2C,
		SOUND_MSG_Seek = 0x2D,
		SOUND_MSG_SetAtListener = 0x2E,
		SOUND_MSG_SetPriority = 0x2F,
		SOUND_MSG_InvalidateAudioSourceID = 0x30,
		SOUND_MSG_SetSoundOutputModel = 0x32,
	};
	struct BSSoundMessage
	{
		// members
		SOUND_MSG       msg;          // 00
		std::uint32_t   soundid;      // 04
		std::uint32_t   time;         // 08
		std::int32_t    unkC;         // 0C
		void*           data;         // 10
		NiAVObject*     source_node;  // 18
		NiPoint3        pos;          // 20
		std::int32_t    unk2C;        // 2C
		BSSoundMessage* next;         // 30
		BSSoundMessage* prev;         // 38
	};
	static_assert(sizeof(BSSoundMessage) == 0x40);

	struct SoundMessageList
	{
		// members
		BSSoundMessage *head;   // 00
		BSSoundMessage *tail;   // 08
	};
	static_assert(sizeof(SoundMessageList) == 0x10);

	class BSGameSound
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSGameSound;

		// add
		virtual void OutputModelChangedImpl();  // 00 - { return; }

		virtual ~BSGameSound();  // 01

		virtual bool IsAsyncOpening ();                                // 02
		virtual void Unk_03();                                         // 03
		virtual void Unk_04() = 0;                                     // 04
		virtual bool PriorityTest (BSGameSound *other);                // 05
		virtual bool SyncOpen() = 0;                                   // 06
		virtual bool StartAsyncOpen() = 0;                             // 07
		virtual bool TestAsyncOpenReady() = 0;                         // 08
		virtual bool FinishAsyncOpen() = 0;                            // 09
		virtual bool HandleExternalOpen() = 0;                         // 0A
		virtual bool Prepare();                                        // 0B
		virtual void Copy (BSGameSound *other, bool a3);               // 0C
		virtual void UpdateEmitterPosition() = 0;                      // 0D
		virtual bool Update ();                                    	   // 0E
		virtual void SetEmitterPositionImpl(const NiPoint3 &pos) = 0;  // 0F
		virtual void GetEmitterPositionImpl(const NiPoint3 &pos) = 0;  // 10
		virtual void Unk_11() = 0;                                     // 11
		virtual void Unk_12() = 0;                                     // 12
		virtual void DoApplyFrequency();                               // 13 - { return; }
		virtual void SeekInSamples(uint32_t a2) = 0;                   // 14
		virtual void PlayImpl() = 0;                                   // 15
		virtual void PauseImpl() = 0;                                  // 16
		virtual void StopImpl(bool a2) = 0;                            // 17
		virtual void SetVolumeImpl() = 0;                              // 18

		// members
		char                requests [24];          // 08
        NiPoint3            beamEnd;                // 20
        std::int32_t        unk2C;                  // 2C
        SoundMessageList    list;                   // 30
        BSResource::ID      resource_id;            // 40
        std::int32_t        soundID;                // 4C
        std::uint32_t       flags;                  // 50
        std::int32_t        field;                  // 54
        std::int32_t        alternateSoundFormId;   // 58
        std::int32_t        flags2;                 // 5C
        std::uint32_t       milliseconds;           // 60
        std::int16_t        attenuation;            // 64
        std::int16_t        unk66;                  // 66
        std::int16_t        unk68;                  // 68
        std::int16_t        unk6A;                  // 6A
        std::int16_t        unk6C;                  // 6C
        char                pad6E[2];               // 6E
        float               volume;                 // 70
        float               unk74;                  // 74
        float               unk78;                  // 78
        std::int32_t        audioBytes;             // 7C
        float               distanceToListener;     // 80
        std::int32_t        unk84;                  // 84
        std::int64_t        unk88;                  // 88
        std::int64_t        callback;               // 90
        std::int64_t        unk98;                  // 98
        std::int64_t        unkA0;                  // A0
        std::uint32_t       priority;               // A8
        std::int32_t        unkAC;                  // AC
        BSISoundCategory    *soundCategory;         // B0
        BSISoundOutputModel *output_model;          // B8
        std::uint8_t        min_frequency;          // C0
        std::uint8_t        frequency_spread;       // C1
        char                unkC2[6];               // C2
	};
	static_assert(sizeof(BSGameSound) == 0xC8);
}
