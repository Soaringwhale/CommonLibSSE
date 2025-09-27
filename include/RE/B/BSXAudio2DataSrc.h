#pragma once

namespace RE
{
	struct WAVFORMATEX
	{
		unsigned short  wFormatTag;      /* format type */
		unsigned short  nChannels;       /* number of channels (i.e. mono, stereo...) */
		unsigned long   nSamplesPerSec;  /* sample rate */
		unsigned long   nAvgBytesPerSec; /* for buffer estimation */
		unsigned short  nBlockAlign;     /* block size of data */
		unsigned short  wBitsPerSample;  /* number of bits per sample of mono data */
		unsigned short  cbSize;          /* the count in bytes of the size of */
							   /* extra information (after cbSize) */
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
		void*                  vftable;
		uint32_t               refCount_8;
		int                    flags;
		void*                  stream;
		int16_t                field_18;
		WAVFORMATEX            SourceFormat;
		char                   pad32[6];
		int                    field_38;
		int                    pad3C;
		int                    playBegin;
		int                    pad44;
		int                    start_sample;
		int                    samples_count;
		int64_t                field_50;
		RiffFile__RiffMetaData riffMetadata;
		int64_t                field_80;
		int                    field_88;
		int                    pad8C;
		int64_t                field_90;
		int                    field_98;
		int                    field_9C;
		int64_t                field_A0;
		uint32_t*              pDecodedPacketCumulativeBytes;
		int                    AudioBytes;
		uint32_t               padB4;
		char*                  pAudioData;
	};
	static_assert(sizeof(BSXAudio2DataSrc) == 0xC0);
}
