#pragma once

#include "RE/B/BSResourceHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/H/hkbAssetLoader.h"

namespace RE
{
	// TODO: implement ctor & dtor
	class BSResourceAssetLoader : public hkbAssetLoader
	{
	public:
		inline static constexpr auto RTTI = RTTI___BSResourceAssetLoader;
		inline static constexpr auto VTABLE = VTABLE___BSResourceAssetLoader;

		struct Entry
		{
			// members
			Entry*         next;    // 00
			hkbHkxDBHandle handle;  // 08
		};
		static_assert(sizeof(Entry) == 0x10);

		BSResourceAssetLoader();

		// 00
		~BSResourceAssetLoader() override;

		// override (hkbAssetLoader)
		void* loadAsset(const char* rootPath, const char* filename, const hkClass& refClass) override;  // 03
		void  unk04(void) override {}                                                                   // 04

		// members
		char                      arena[0x40];     // 20 - BSTObjectArena<Entry>
		char                      buffer[8];       // 60 - AutoScrapBuffer
		Entry*                    lastAddedEntry;  // 68
		hkbHkxDBHandle            handle;          // 70
		BSTArray<hkbHkxDBHandle>* handles;         // 78
		uint8_t                   unk80;           // 80
		uint8_t                   unk81;           // 80
		uint16_t                  unk82;           // 80
		uint32_t                  unk84;           // 84
	};
	static_assert(sizeof(BSResourceAssetLoader) == 0x88);
}
