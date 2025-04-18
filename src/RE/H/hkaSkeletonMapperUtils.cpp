#include "RE/H/hkaSkeletonMapperUtils.h"

namespace RE
{
	namespace hkaSkeletonMapperUtils
	{
		void createMapping(const Params& params, hkaSkeletonMapperData& aToB, hkaSkeletonMapperData& bToA)
		{
			using func_t = decltype(createMapping);
			REL::Relocation<func_t> func{ RELOCATION_ID(78247, 0) };
			return func(params, aToB, bToA);
		}
	}
}
