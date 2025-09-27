#pragma once

namespace RE
{
	struct WAVFORMATEX
	{
		std::uint16_t wFormatTag;      /* format type */
		std::uint16_t nChannels;       /* number of channels (i.e. mono, stereo...) */
		std::uint32_t nSamplesPerSec;  /* sample rate */
		std::uint32_t nAvgBytesPerSec; /* for buffer estimation */
		std::uint16_t nBlockAlign;     /* block size of data */
		std::uint16_t wBitsPerSample;  /* number of bits per sample of mono data */
		std::uint16_t cbSize;          /* the count in bytes of the size of extra information */
	};
	static_assert(sizeof(WAVFORMATEX) == 0x14);

	struct RiffFile__RiffMetaData
	{
      public:
		WAVFORMATEX*    waveFormat;     // 00
		std::uint32_t   dataOffset;     // 08  
		std::uint32_t   dataSize;       // 0C - audioBytes
		std::uint32_t   suppDataOffset; // 10
		std::uint32_t   suppDataSize;   // 14  
		std::uint32_t   param1;         // 18
		std::uint32_t   param2;         // 1C
		std::uint32_t   parseFlags;     // 20
		std::uint32_t   reserved;       // 24
	};
	static_assert(sizeof(RiffFile__RiffMetaData) == 0x28);
	 
	class BSXAudio2DataSrc
	{
	  public:
		void*                  vftable;							 // 00
		std::uint32_t          refCount;						 // 08
		std::int32_t           flags;							 // 0C
		void*                  stream;							 // 10
		std::int16_t           unk18;							 // 18
		WAVFORMATEX            SourceFormat;					 // 1C
		char                   unk32[6];						 // 30
		std::int32_t           unk38;							 // 38
		std::int32_t           unk3C;							 // 3C
		std::int32_t           playBegin;						 // 40
		std::int32_t           unk44;							 // 44
		std::int32_t           start_sample;					 // 48
		std::int32_t           samples_count;					 // 4C
		std::int64_t           unk50;							 // 50
		RiffFile__RiffMetaData riffMetadata;					 // 58
		std::int64_t           unk80;							 // 80
		std::int32_t           unk88;							 // 88
		std::int32_t           pad8C;							 // 8C
		std::int64_t           unk90;							 // 90
		std::int32_t           unk98;							 // 98
		std::int32_t           unk9C;							 // 9C
		std::int64_t           unkA0;							 // A0
		std::uint32_t*         pDecodedPacketCumulativeBytes;    // A8
		std::int32_t           AudioBytes;						 // B0
		std::uint32_t          unkB4;							 // B4
		char*                  pAudioData;						 // B8
	};
	static_assert(sizeof(BSXAudio2DataSrc) == 0xC0);
}
