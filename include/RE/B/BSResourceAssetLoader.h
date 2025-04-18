#pragma once

#include "RE/B/BSTArray.h"
#include "RE/H/hkbAssetLoader.h"

namespace RE
{
	class BSResourceAssetLoader : public hkbAssetLoader
	{
	public:
		BSResourceAssetLoader()
		{
			using func_t = BSResourceAssetLoader*(BSResourceAssetLoader*);
			REL::Relocation<func_t> func{ RELOCATION_ID(62966, 0) };
			func(this);
		}
		// 00
		~BSResourceAssetLoader() override {
			using func_t = BSResourceAssetLoader*(BSResourceAssetLoader*);
			REL::Relocation<func_t> func{ RELOCATION_ID(62949, 0) };
			func(this);
		}

		// override (hkbAssetLoader)
		
		// 03
		void* loadAsset(const char* rootPath, const char* filename, const hkClass& refClass) override
		{
			using func_t = decltype(&BSResourceAssetLoader::loadAsset);
			REL::Relocation<func_t> func{ RELOCATION_ID(62950, 0) };
			return func(this, rootPath, filename, refClass);
		}
		void  unk04(void) override {}                                                                     // 04

		// members
		char             arena[0x40];      // 20 - BSTObjectArena<?>
		char             buffer[8];        // 60 - AutoScrapBuffer
		uint64_t         unk68;            // 68
		uint64_t         unk70;            // 70
		BSTArray<void*>* hashedBehaviors;  // 78
		uint8_t          unk80;            // 80
		uint8_t          unk81;            // 80
		uint16_t         unk82;            // 80
		uint32_t         unk84;            // 84
	};
	static_assert(sizeof(BSResourceAssetLoader) == 0x88);
}
