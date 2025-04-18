#include "RE/H/hkaSkeletonMapper.h"

#include "RE/H/hkaAnimationBinding.h"

namespace RE
{
	void hkaSkeletonMapper::initializeBindingMaps(const hkaAnimationBinding* binding, hkArray<int16_t>& srcBoneToTrackIndicesOut, hkArray<int16_t>& dstBoneToTrackIndicesOut, hkArray<int16_t>& dstTrackToBoneIndicesOut) const
	{
		using func_t = decltype(&hkaSkeletonMapper::initializeBindingMaps);
		REL::Relocation<func_t> func{ RELOCATION_ID(63157, 0) };
		return func(this, binding, srcBoneToTrackIndicesOut, dstBoneToTrackIndicesOut, dstTrackToBoneIndicesOut);
	}
}
