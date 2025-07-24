#include "RE/B/BSFaceGenUtils.h"

namespace RE
{
	namespace BSFaceGenUtils
	{
		void AddHeadPartOnActor(Actor* a, BGSHeadPart* part)
		{
			using func_t = decltype(AddHeadPartOnActor);
			REL::Relocation<func_t> func{ RELOCATION_ID(26466, 27061) };
			return func(a, part);
		}

		bool ApplyMasksToRenderTargets(BSTArray<TintMask*>& tint_masks, NiSourceTexture* texture)
		{
			using func_t = decltype(ApplyMasksToRenderTargets);
			REL::Relocation<func_t> func{ RELOCATION_ID(26454, 27040) };
			return func(tint_masks, texture);
		}

		void CopyBaseVertsToBackBuffer(BSFaceGenNiNode* node)
		{
			using func_t = decltype(CopyBaseVertsToBackBuffer);
			REL::Relocation<func_t> func{ RELOCATION_ID(26458, 27044) };
			return func(node);
		}

		void RemoveHeadPartOnActor(Actor* a, BGSHeadPart* part)
		{
			using func_t = decltype(RemoveHeadPartOnActor);
			REL::Relocation<func_t> func{ RELOCATION_ID(26467, 27062) };
			return func(a, part);
		}

		void ReplaceHeadPartOnActor(Actor* a, BGSHeadPart* cur_part, BGSHeadPart* new_part)
		{
			using func_t = decltype(ReplaceHeadPartOnActor);
			REL::Relocation<func_t> func{ RELOCATION_ID(26468, 0) };
			return func(a, cur_part, new_part);
		}

		void SetBodyColor(Actor* a, const NiColor& color)
		{
			using func_t = decltype(SetBodyColor);
			REL::Relocation<func_t> func{ RELOCATION_ID(26464, 27059) };
			return func(a, color);
		}

		void SetHairColor(Actor* a, const NiColor& color)
		{
			using func_t = decltype(SetHairColor);
			REL::Relocation<func_t> func{ RELOCATION_ID(26465, 27060) };
			return func(a, color);
		}
	}
}
