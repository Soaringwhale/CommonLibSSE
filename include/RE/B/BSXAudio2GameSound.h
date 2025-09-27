#pragma once

#include "RE/B/BSGameSound.h"
#include "RE/I/IXAudio2VoiceCallback.h"
#include "RE/B/BSXAudio2DataSrc.h"

namespace RE
{
	class IXAudio2SourceVoice;

	class BSXAudio2GameSound :
		public BSGameSound,           // 000
		public IXAudio2VoiceCallback  // 0C8
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSXAudio2GameSound;

		// override (BSGameSound)
		void OutputModelChangedImpl(void) override;                    // 00
		~BSXAudio2GameSound() override;                                // 01
        void Unk_04(void) override;                                    // 04
        bool SyncOpen(void) override;                                  // 06
		bool StartAsyncOpen(void) override;                            // 07
		bool TestAsyncOpenReady(void) override;                        // 08
		bool FinishAsyncOpen(void) override;                           // 09
		bool HandleExternalOpen(void) override;                        // 0A
		bool Prepare(void) override;                                   // 0B
		void Copy(BSGameSound *other, bool a3) override;               // 0C
		void UpdateEmitterPosition(void) override;                     // 0D
		bool Update(void) override;                                    // 0E
		void SetEmitterPositionImpl(const NiPoint3 &pos) override;     // 0F
	    void GetEmitterPositionImpl(const NiPoint3 &outPos) override;  // 10
		void Unk_11(void) override;                                    // 11
		void Unk_12(void) override;                                    // 12
		void DoApplyFrequency(void) override;                          // 13
		void SeekInSamples(uint32_t a2) override;                      // 14
		void PlayImpl(void) override;                                  // 15
		void PauseImpl(void) override;                                 // 16
		void StopImpl(bool a2) override;                               // 17
		void SetVolumeImpl(void) override;                             // 18

		void                *vtable_IXAudio2VoiceCallback;   // C8
		BSXAudio2DataSrc    *data_src;       // D0
		int32_t             unkD8;           // D8
		int16_t             unkDC;           // DC
		int16_t             unkDE;           // DE
		float               *unkE0;          // E0
		int32_t             unkE8;           // E8
		float               floats[12];      // F0
		int32_t             unk11C;          // 11C
		int32_t             unk120;          // 120
		uint32_t            samples;         // 124
		IXAudio2SourceVoice *sourceVoice;    // 128
		int64_t             unk130;          // 130
		int64_t             unk138;          // 138
		int32_t             unk140;          // 140
		int32_t             unk144;          // 144
		int64_t             unk148;          // 148
		int64_t             unk150;          // 150
		int64_t             unk158;          // 158
		int64_t             unk160;          // 160
		float               *unk168;         // 168
		int64_t             unk170;          // 170
		int64_t             unk178;          // 178
		int64_t             unk180;          // 180
		NiPoint3            p2;              // 188
		int32_t             unk194;          // 194
		int64_t             unk198;          // 198
		int64_t             unk1A0;          // 1A0
		int32_t             unk1A8;          // 1A8
		int32_t             unk1AC;          // 1AC
		float               **unk1B0;        // 1B0
		int32_t             *unk1B8;         // 1B8
		int64_t             unk1C0;          // 1C0
		int64_t             unk1C8;          // 1C8
		int64_t             unk1D0;          // 1D0
		int64_t             unk1D8;          // 1D8
		float               unk1E0;          // 1E0
		float               unk1E4;          // 1E4
		float               unk1E8;          // 1E8
		int32_t             unk1EC;          // 1EC
		float               unk1F0;          // 1F0
		int32_t             unk1F4;          // 1F4
		int64_t             unk1F8;          // 1F8
		int64_t             unk200;          // 200
		int32_t             unk208;          // 208
		uint64_t            unk210[1];       // 210
		int64_t             unk218;          // 218

	};
	static_assert(sizeof(BSXAudio2GameSound) == 0x220);
}
