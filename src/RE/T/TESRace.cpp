#include "RE/T/TESRace.h"

namespace RE
{
	bool TESRace::AllowsPCDialogue() const
	{
		return data.flags.all(RACE_DATA::Flag::kAllowPCDialogue);
	}

	bool TESRace::AllowsPickpocket() const
	{
		return data.flags.all(RACE_DATA::Flag::kAllowPickpocket);
	}

	TESRace::FaceRelatedData::TintAsset* TESRace::getTintAsset(SEX sex, FaceRelatedData::TintAsset::TintLayer::SkinTone tone,
		int32_t ind) const
	{
		int32_t skipped = 0;
		if (auto faceData = faceRelatedData[sex]) {
			if (auto tintMasks = faceData->tintMasks) {
				for (auto mask : *tintMasks) {
					if (mask->texture.skinTone == tone) {
						if (skipped == ind)
							return mask;
						else
							++skipped;
					}
				}
			}
		}
		return nullptr;
	}

	bool TESRace::IsChildRace() const
	{
		return data.flags.all(RACE_DATA::Flag::kChild);
	}
}
