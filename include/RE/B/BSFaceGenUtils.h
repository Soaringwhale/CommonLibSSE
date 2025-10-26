#pragma once

#include "RE/B/BSTArray.h"
#include "RE/C/Color.h"

namespace RE
{
	class Actor;
	class BGSHeadPart;
	class BSFaceGenNiNode;
	class TESTexture;
	class NiColor;
	class NiSourceTexture;

	class TintMask
	{
	public:
		TintMask() = default;
		~TintMask() = default;

		// members
		TESTexture* texture{ nullptr };  // 00
		Color       color{};             // 08
		float       alpha{ 0 };          // 10
		uint32_t    skinTone{};          // 14 - TESRace::FaceRelatedData::TintAsset::TintLayer::SkinTone, but 32 bits
	};
	static_assert(sizeof(TintMask) == 0x18);

	namespace BSFaceGenUtils
	{
		void AddHeadPartOnActor(Actor* a, BGSHeadPart* part);
		bool ApplyMasksToRenderTargets(BSTArray<TintMask*>& tint_masks, NiSourceTexture* texture);
		void CopyBaseVertsToBackBuffer(BSFaceGenNiNode* node);
		void RemoveHeadPartOnActor(Actor* a, BGSHeadPart* part);
		void ReplaceHeadPartOnActor(Actor* a, BGSHeadPart* cur_part, BGSHeadPart* new_part);
		void SetBodyColor(Actor* a, const NiColor& color);
		void SetHairColor(Actor* a, const NiColor& color);
	}
}
