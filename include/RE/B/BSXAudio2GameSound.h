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
		void OutputModelChangedImpl() override;                        // 00
		~BSXAudio2GameSound() override;                                // 01
		void Unk_04() override;                                        // 04
		bool SyncOpen() override;                                      // 06
		bool StartAsyncOpen() override;                                // 07
		bool TestAsyncOpenReady() override;                            // 08
		bool FinishAsyncOpen() override;                               // 09
		bool HandleExternalOpen() override;                            // 0A
		bool Prepare() override;                                       // 0B
		void Copy(BSGameSound *other, bool a3) override;               // 0C
		void UpdateEmitterPosition() override;                         // 0D
		bool Update() override;                                        // 0E
		void SetEmitterPositionImpl(const NiPoint3 &pos) override;     // 0F
		void GetEmitterPositionImpl(const NiPoint3 &outPos) override;  // 10
		void Unk_11() override;                                        // 11
		void Unk_12() override;                                        // 12
		void DoApplyFrequency() override;                              // 13
		void SeekInSamples(uint32_t a2) override;                      // 14
		void PlayImpl() override;                                      // 15
		void PauseImpl() override;                                     // 16
		void StopImpl(bool a2) override;                               // 17
		void SetVolumeImpl() override;                                 // 18

		// members
		void                *vtable_IXAudio2VoiceCallback;   // C8
		BSXAudio2DataSrc    *data_src;       // D0
		std::int32_t        unkD8;           // D8
		std::int16_t        unkDC;           // DC
		std::int16_t        unkDE;           // DE
		float               *unkE0;          // E0
		std::int32_t        unkE8;           // E8
		float               floats[12];      // F0
		std::int32_t        unk11C;          // 11C
		std::int32_t        unk120;          // 120
		std::uint32_t       samples;         // 124
		IXAudio2SourceVoice *sourceVoice;    // 128
		std::int64_t        unk130;          // 130
		std::int64_t        unk138;          // 138
		std::int32_t        unk140;          // 140
		std::int32_t        unk144;          // 144
		std::int64_t        unk148;          // 148
		std::int64_t        unk150;          // 150
		std::int64_t        unk158;          // 158
		std::int64_t        unk160;          // 160
		float               *unk168;         // 168
		std::int64_t        unk170;          // 170
		std::int64_t        unk178;          // 178
		std::int64_t        unk180;          // 180
		NiPoint3            p2;              // 188
		std::int32_t        unk194;          // 194
		std::int64_t        unk198;          // 198
		std::int64_t        unk1A0;          // 1A0
		std::int32_t        unk1A8;          // 1A8
		std::int32_t        unk1AC;          // 1AC
		float               **unk1B0;        // 1B0
		std::int32_t        *unk1B8;         // 1B8
		std::int64_t        unk1C0;          // 1C0
		std::int64_t        unk1C8;          // 1C8
		std::int64_t        unk1D0;          // 1D0
		std::int64_t        unk1D8;          // 1D8
		float               unk1E0;          // 1E0
		float               unk1E4;          // 1E4
		float               unk1E8;          // 1E8
		std::int32_t        unk1EC;          // 1EC
		float               unk1F0;          // 1F0
		std::int32_t        unk1F4;          // 1F4
		std::int64_t        unk1F8;          // 1F8
		std::int64_t        unk200;          // 200
		std::int32_t        unk208;          // 208
		std::uint64_t       unk210[1];       // 210
		std::int64_t        unk218;          // 218

	};
	static_assert(sizeof(BSXAudio2GameSound) == 0x220);
}
