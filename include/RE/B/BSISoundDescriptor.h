#pragma once
#include "RE/I/ID.h"
#include "RE/B/BSTArray.h"

namespace RE
{
	class BSISoundOutputModel;
	class BSISoundCategory;
	struct BSAudioMonitor_Request
	{
		int32_t unk0;
	};
	class BSISoundDescriptor
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSISoundDescriptor;

		class BSIPlaybackCharacteristics
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSISoundDescriptor__BSIPlaybackCharacteristics;

			virtual ~BSIPlaybackCharacteristics();  // 00

			// add
			virtual std::uint8_t  GetFrequencyShift() = 0;     // 01
			virtual std::uint8_t  GetFrequencyVariance() = 0;  // 02
			virtual std::uint8_t  GetPriority() = 0;           // 03
			virtual std::uint16_t GetStaticAttenuation() = 0;  // 04
			virtual std::uint8_t  GetDBVariance() = 0;         // 05
		};
		static_assert(sizeof(BSIPlaybackCharacteristics) == 0x8);
 
		struct Resolution
		{
			RE::BSResource::ID                                 resource;                 // 00
			int                                                field;                    // 0C
			int                                                AlternateSoundFormId;     // 10
			int                                                flags;                    // 14
			BSIPlaybackCharacteristics*                        PlaybackCharacteristics;  // 18
			BSISoundOutputModel*                               OutputModel;              // 20
			BSISoundCategory*                                  soundCategory;            // 28
			BSTSmallArray<BSAudioMonitor_Request, 2>           requests;                 // 30
		};
		static_assert(sizeof(Resolution) == 0x48);

		virtual ~BSISoundDescriptor();  // 00

		// add
		virtual bool DoResolve (Resolution &res) = 0;  // 01
		virtual void Unk_02(void) = 0;                 // 02
	};
	static_assert(sizeof(BSISoundDescriptor) == 0x8);
}
