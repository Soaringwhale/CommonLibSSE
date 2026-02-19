#pragma once

#include "RE/B/BSTSmartPointer.h"
#include "RE/S/Stream.h"

namespace RE
{
	struct WAVFORMATEX
	{ 
		// members
		std::uint16_t wFormatTag;         // 00 - format type
		std::uint16_t nChannels;          // 02 - number of channels (i.e. mono, stereo...)
		std::uint32_t nSamplesPerSec;     // 04 - sample rate
		std::uint32_t nAvgBytesPerSec;    // 08 - for buffer estimation
		std::uint16_t nBlockAlign;        // 0C - block size of data
		std::uint16_t wBitsPerSample;     // 0E - number of bits per sample of mono data
		std::uint16_t cbSize;             // 10 - the count in bytes of the size of extra information
	};
	static_assert(sizeof(WAVFORMATEX) == 0x14);

	struct RiffFile__RiffMetaData
	{
		// members
		WAVFORMATEX*    waveFormat;        // 00
		std::uint32_t   dataOffset;        // 08  
		std::uint32_t   dataSize;          // 0C - audioBytes
		std::uint32_t   suppDataOffset;    // 10
		std::uint32_t   suppDataSize;      // 14  
		std::uint32_t   loopStartSample;   // 18
		std::uint32_t   loopEndSample;     // 1C
		std::uint32_t   parseFlags;        // 20
		std::uint32_t   reserved;          // 24
	};
	static_assert(sizeof(RiffFile__RiffMetaData) == 0x28);
	 
	class BSXAudio2DataSrc
	{
	public:
		void*                                       vftable;                        // 00
		std::uint32_t                               refCount;                       // 08
		std::int32_t                                flags;                          // 0C
		RE::BSTSmartPointer<RE::BSResource::Stream> stream;                         // 10
		void*                                       externalData;                   // 18
		WAVFORMATEX                                 sourceFormat;                   // 20
		std::int32_t                                unk34;                          // 34
		std::int32_t                                unk38;                          // 38
		std::int32_t                                unk3C;                          // 3C
		std::int32_t                                playBegin;                      // 40
		std::int32_t                                unk44;                          // 44
		std::int32_t                                start_sample;                   // 48
		std::int32_t                                samples_count;                  // 4C
		std::int64_t                                unk50;                          // 50
		RiffFile__RiffMetaData                      riffMetadata;                   // 58
		void*                                       unk80;                          // 80
		std::int32_t                                unk88;                          // 88
		std::int32_t                                pad8C;                          // 8C
		void*                                       allocatedAudioBuffer;           // 90
		std::int32_t                                asyncAudioDataSize;             // 98
		std::int32_t                                allocatedBufferSize;            // 9C
		void*                                       asyncAudioSourceData;           // A0
		std::uint32_t*                              pDecodedPacketCumulativeBytes;  // A8
		std::int32_t                                audioBytes;                     // B0
		std::uint32_t                               unkB4;                          // B4
		char*                                       pAudioData;                     // B8
	};
	static_assert(sizeof(BSXAudio2DataSrc) == 0xC0);
}
