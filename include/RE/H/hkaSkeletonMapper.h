#pragma once

#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkaSkeletonMapperData.h"

namespace RE
{
	class hkaAnimationBinding;

	class hkaSkeletonMapper : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkaSkeletonMapper;
		inline static constexpr auto VTABLE = VTABLE_hkaSkeletonMapper;

		HK_HEAP_REDEFINE_NEW();

		hkaSkeletonMapper(const hkaSkeletonMapperData& a_mapping) :
			mapping(a_mapping) { stl::emplace_vtable(this); }
		~hkaSkeletonMapper() = default;

		/// This function creates additional binding information
		/// needed when retargeting partial (sparse) animations.
		/// Given an animation intended for skeletonA (src), the
		/// m_transformTrackToBoneIndices are inverted to form
		/// boneToTrack indices. Additionally trackToBone and
		/// boneToTrack indices are created for skeletonB (dst)
		/// using the mapping from the hkaSkeletonMapperData.
		/// Unmapped bones and incomplete chains in skeletonA
		/// are culled from the dst arrays.
		void initializeBindingMaps(const hkaAnimationBinding* binding, hkArray<int16_t>& srcBoneToTrackIndicesOut, hkArray<int16_t>& dstBoneToTrackIndicesOut, hkArray<int16_t>& dstTrackToBoneIndicesOut) const;

		// members
		hkaSkeletonMapperData mapping;  // 10
	};
	static_assert(sizeof(hkaSkeletonMapper) == 0x90);
}
