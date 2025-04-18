#include "RE/H/hkReferencedObject.h"

namespace RE
{
	void hkReferencedObject::CalcContentStatistics(hkStatisticsCollector* a_collector, const hkClass* a_class) const
	{
		using func_t = decltype(&hkReferencedObject::CalcContentStatistics);
		REL::Relocation<func_t> func{ RELOCATION_ID(56617, 0) };
		return func(this, a_collector, a_class);
	}

	void hkReferencedObject::AddReference() const
	{
		using func_t = decltype(&hkReferencedObject::AddReference);
		REL::Relocation<func_t> func{ Offset::hkReferencedObject::AddReference };
		return func(this);
	}

	std::int32_t hkReferencedObject::GetAllocatedSize() const
	{
		return memSizeAndFlags & kMemSize;
	}

	void hkReferencedObject::RemoveReference() const
	{
		using func_t = decltype(&hkReferencedObject::RemoveReference);
		REL::Relocation<func_t> func{ Offset::hkReferencedObject::RemoveReference };
		return func(this);
	}
}
