#include "RE/I/IPipelineStageInterface.h"

namespace RE
{
	IPipelineStageInterface::IPipelineStageInterface()
	{
		stl::emplace_vtable(this);
	}
}
