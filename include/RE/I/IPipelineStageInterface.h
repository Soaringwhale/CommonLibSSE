#pragma once

namespace RE
{
	struct IPipelineStageInterface
	{
		inline static constexpr auto RTTI = RTTI_IPipelineStageInterface;
		inline static constexpr auto VTABLE = VTABLE_IPipelineStageInterface;

		IPipelineStageInterface();

		virtual ~IPipelineStageInterface() = default;  // 00
	};
	static_assert(sizeof(IPipelineStageInterface) == 0x8);
}
