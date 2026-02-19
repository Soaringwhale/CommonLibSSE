#pragma once

#include "RE/I/IXAudio2Voice.h"

namespace RE
{
	struct XAUDIO2_BUFFER
	{
		//members
		std::uint32_t flags;       // 00
		std::int32_t  audioBytes;  // 04
		char*         pAudioData;  // 08
		std::int32_t  playBegin;   // 10
		std::int32_t  playLength;  // 14
		std::int32_t  loopBegin;   // 18
		std::int32_t  loopLength;  // 1C
		std::int32_t  loopCount;   // 20
		std::int32_t  pad_24;      // 24
		void*         pContext;    // 28
	};
	static_assert(sizeof(XAUDIO2_BUFFER) == 0x30);

	struct XAUDIO2_BUFFER_WMA
	{
		//members
		std::uint32_t* pDecodedPacketCumulativeBytes;  // 00
		std::int32_t   packetCount;                    // 08
	};
	static_assert(sizeof(XAUDIO2_BUFFER_WMA) == 0x10);

	#pragma pack(push, 1)
	struct XAUDIO2_VOICE_STATE
	{
		//members
		void*          pCurrentBufferContext;  // 00
		std::int32_t   buffersQueued;          // 08
		std::uint64_t  samplesPlayed;          // 0C
	};
	#pragma pack(pop)
	static_assert(sizeof(XAUDIO2_VOICE_STATE) == 0x14);

	class IXAudio2SourceVoice : public IXAudio2Voice
	{
	public:
		// add
		virtual std::int32_t  Start(std::uint32_t a_flags, std::uint32_t a_OperationSet);                    // 13
		virtual std::int32_t  Stop (std::uint32_t a_flags, std::uint32_t a_OperationSet);                    // 14
		virtual std::int32_t  SubmitSourceBuffer (XAUDIO2_BUFFER *pBuffer, XAUDIO2_BUFFER_WMA *pBufferWMA);  // 15
		virtual std::int32_t  FlushSourceBuffers ();                                                         // 16
		virtual void          Unk_17 ();                                                                     // 17
		virtual std::int32_t  ExitLoop (std::uint32_t OperationSet);                                         // 18
		virtual std::int32_t  GetState (XAUDIO2_VOICE_STATE &state);                                         // 19
		virtual std::int32_t  SetFrequencyRatio (float a_Ratio, std::uint32_t a3);                           // 1A
	};
	static_assert(sizeof(IXAudio2SourceVoice) == 0x8);
}
