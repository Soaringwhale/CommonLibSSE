#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkaSkeletonMapperData.h"

namespace RE
{
	class hkaSkeleton;

	namespace hkaSkeletonMapperUtils
	{
		struct ExtractedMotionParams
		{
			enum class ExtractedMotionMode : int32_t
			{
				HK_USE_BOUNDING_BOX_DIAGONAL = 0,
				HK_USE_BONE_LENGTHS = 1,
				HK_USE_FACTORS_DIRECTLY = 2
			};

			// members
			ExtractedMotionMode m_mode{ ExtractedMotionMode::HK_USE_BOUNDING_BOX_DIAGONAL };  // 00
			int32_t             m_extractedMotionBoneA{ 0 };                                  // 04
			int32_t             m_extractedMotionBoneB{ 0 };                                  // 08
			float               m_extractedMotionFactorA{ 1.0f };                             // 0C
			float               m_extractedMotionFactorB{ 1.0f };                             // 10
		};
		static_assert(sizeof(ExtractedMotionParams) == 0x14);

		/// A explicit mapping (one-way only) - used in Params::m_userMappingsAtoB and Params::m_userMappingsBtoA.
		/// The names will be matched with the bones names (after filtering the names) of the skeleton (A or B).
		/// These correspond to partition names when computing partition mapping.
		struct UserMapping
		{
			// members
			const char* m_boneIn;   // 00
			const char* m_boneOut;  // 08
		};
		static_assert(sizeof(UserMapping) == 0x10);

		/// These struct contains all the information used by "createMapping" in order to construct mapping data
		struct Params
		{
			Params() = default;

			// members
			hkaSkeleton*                       m_skeletonA{ nullptr };                                                   // 00
			hkaSkeleton*                       m_skeletonB{ nullptr };                                                   // 08
			void*                              m_compareNames{ nullptr };                                                // 10
			float                              m_positionMatchTolerance{ 0 };                                            // 18
			float                              m_rotationMatchTolerance{ 30.0f * 3.1415926f / 180.0f };                  // 1C
			hkArray<void*>                     m_userChains;                                                             // 20
			hkArray<UserMapping>               m_userMappingsAtoB;                                                       // 30
			hkArray<UserMapping>               m_userMappingsBtoA;                                                       // 40
			bool                               m_autodetectSimple{ true };                                               // 50
			bool                               m_autodetectChains{ true };                                               // 51
			char                               pad52[2];                                                                 // 52
			hkaSkeletonMapperData::MappingType m_mappingType{ hkaSkeletonMapperData::MappingType::HK_RAGDOLL_MAPPING };  // 54
			ExtractedMotionParams              m_motionParams;                                                           // 58
			char                               pad6C[4];                                                                 // 6C
		};
		static_assert(sizeof(Params) == 0x70);

		void createMapping(const Params& params, hkaSkeletonMapperData& aToB, hkaSkeletonMapperData& bToA);
	}
}
