#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkbAssetLoader : public hkReferencedObject
	{
	public:
		hkbAssetLoader() = default;
		~hkbAssetLoader() override = default;  // 00

		// add
		virtual void* loadAsset(const char* rootPath, const char* filename, const hkClass& refClass) = 0;  // 03
		virtual void  unk04(void) = 0;                                                                     // 04

		// members
		hkArray<uint64_t> array;  // 10
	};
	static_assert(sizeof(hkbAssetLoader) == 0x20);
}
