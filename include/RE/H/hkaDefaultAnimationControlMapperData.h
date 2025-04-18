#pragma once

#include "RE/H/hkaSkeletonMapper.h"

namespace RE
{
	class hkaDefaultAnimationControlMapperData : public hkReferencedObject
	{
	public:
		hkaDefaultAnimationControlMapperData(hkaSkeletonMapper* mapper, hkaAnimationBinding* binding) :
			m_mapper(mapper)
		{
			m_mapper->initializeBindingMaps(binding, m_srcBoneToTrackIndices, m_dstBoneToTrackIndices, m_dstTrackToBoneIndices);
		}
		~hkaDefaultAnimationControlMapperData() = default;

		HK_HEAP_REDEFINE_NEW();

		// members
		hkRefPtr<hkaSkeletonMapper> m_mapper;                 // 10
		hkArray<int16_t>            m_srcBoneToTrackIndices;  // 18
		hkArray<int16_t>            m_dstBoneToTrackIndices;  // 28
		hkArray<int16_t>            m_dstTrackToBoneIndices;  // 38
	};
	static_assert(sizeof(hkaDefaultAnimationControlMapperData) == 0x48);

}
