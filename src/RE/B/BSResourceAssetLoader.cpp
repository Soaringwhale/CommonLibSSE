#include "RE/B/BSResourceAssetLoader.h"

namespace RE
{
	BSResourceAssetLoader::BSResourceAssetLoader()
	{
		using func_t = BSResourceAssetLoader*(BSResourceAssetLoader*);
		REL::Relocation<func_t> func{ RELOCATION_ID(62966, 0) };
		func(this);
	}

	BSResourceAssetLoader::~BSResourceAssetLoader()
	{
		using func_t = BSResourceAssetLoader*(BSResourceAssetLoader*);
		REL::Relocation<func_t> func{ RELOCATION_ID(62949, 0) };
		func(this);
	}

	void* BSResourceAssetLoader::loadAsset(const char* rootPath, const char* filename, const hkClass& refClass)
	{
		using func_t = decltype(&BSResourceAssetLoader::loadAsset);
		REL::Relocation<func_t> func{ RELOCATION_ID(62950, 0) };
		return func(this, rootPath, filename, refClass);
	}
}
