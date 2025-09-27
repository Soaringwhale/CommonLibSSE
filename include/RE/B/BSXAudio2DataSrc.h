#pragma once

namespace RE
{
	struct WAVFORMATEX
	{
		uint16_t wFormatTag;      /* format type */
		uint16_t nChannels;       /* number of channels (i.e. mono, stereo...) */
		uint32_t nSamplesPerSec;  /* sample rate */
		uint32_t nAvgBytesPerSec; /* for buffer estimation */
		uint16_t nBlockAlign;     /* block size of data */
		uint16_t wBitsPerSample;  /* number of bits per sample of mono data */
		uint16_t cbSize;          /* the count in bytes of the size of extra information */
	};
	static_assert(sizeof(WAVFORMATEX) == 0x14);

	struct RiffFile__RiffMetaData
	{
      public:
		WAVFORMATEX*    waveFormat;     // 00
		uint32_t        dataOffset;     // 08  
		uint32_t        dataSize;       // 0C - audioBytes
		uint32_t        suppDataOffset; // 10
		uint32_t        suppDataSize;   // 14  
		uint32_t        param1;         // 18
		uint32_t        param2;         // 1C
		uint32_t        parseFlags;     // 20
		uint32_t        reserved;       // 24
	};
	static_assert(sizeof(RiffFile__RiffMetaData) == 0x28);
	 
	class BSXAudio2DataSrc
	{
	  public:
		void*                  vftable;							 // 00
		uint32_t               refCount;						 // 08
		int                    flags;							 // 0C
		void*                  stream;							 // 10
		int16_t                unk18;							 // 18
		WAVFORMATEX            sourceFormat;					 // 1C
		char                   unk32[6];						 // 30
		int                    unk38;							 // 38
		int                    unk3C;							 // 3C
		int                    playBegin;						 // 40
		int                    unk44;							 // 44
		int                    start_sample;					 // 48
		int                    samples_count;					 // 4C
		int64_t                unk50;							 // 50
		RiffFile__RiffMetaData riffMetadata;					 // 58
		int64_t                unk80;							 // 80
		int                    unk88;							 // 88
		int                    pad8C;							 // 8C
		int64_t                unk90;							 // 90
		int                    unk98;							 // 98
		int                    unk9C;							 // 9C
		int64_t                unkA0;							 // A0
		uint32_t*              pDecodedPacketCumulativeBytes;    // A8
		int                    AudioBytes;						 // B0
		uint32_t               unkB4;							 // B4
		char*                  pAudioData;						 // B8
	};
	static_assert(sizeof(BSXAudio2DataSrc) == 0xC0);
}
