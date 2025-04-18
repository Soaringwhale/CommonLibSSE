#include "RE/H/hkbBindable.h"

namespace RE
{
	hkbVariableBindingSet::Binding::Binding(const char* memberPath, int32_t variableIndex, BindingType bindingType, int8_t bitIndex) :
		memberPath{ memberPath }, variableIndex(variableIndex), bitIndex(bitIndex), bindingType(bindingType)
	{}

	void hkbVariableBindingSet::addBinding(const char* memberPath, int32_t variableIndex, Binding::BindingType bindingType, int8_t bitIndex)
	{
		if (!std::strcmp(memberPath, "enable"))
			indexOfBindingToEnable = bindings.size();
		bindings.push_back({ memberPath, variableIndex, bindingType, bitIndex });
	}

	bool hkbVariableBindingSet::has_binding(const char* memberPath, int32_t variableIndex, Binding::BindingType bindingType, int8_t bitIndex) const
	{
		Binding test_binding(memberPath, variableIndex, bindingType, bitIndex);

		for (auto& binding : bindings) {
			if (binding == test_binding)
				return true;
		}

		return false;
	}

	void hkbBindable::add_binding(const char* memberPath, int32_t variableIndex, hkbVariableBindingSet::Binding::BindingType bindingType, int8_t bitIndex)
	{
		variableBindingSet->addBinding(memberPath, variableIndex, bindingType, bitIndex);
	}

	void hkbBindable::add_binding_nullcheck(const char* memberPath, int32_t variableIndex, hkbVariableBindingSet::Binding::BindingType bindingType, int8_t bitIndex)
	{
		if (!variableBindingSet) {
			variableBindingSet = RE::hkRefPtr(new RE::hkbVariableBindingSet());
		}
		add_binding(memberPath, variableIndex, bindingType, bitIndex);
	}

	bool hkbBindable::has_binding(const char* memberPath, int32_t variableIndex, hkbVariableBindingSet::Binding::BindingType bindingType, int8_t bitIndex) const
	{
		return variableBindingSet && variableBindingSet->has_binding(memberPath, variableIndex, bindingType, bitIndex);
	}

	bool operator==(const hkbVariableBindingSet::Binding& lhs, const hkbVariableBindingSet::Binding& rhs)
	{
		return lhs.variableIndex == rhs.variableIndex &&
		       lhs.memberPath == rhs.memberPath &&
		       lhs.bindingType == rhs.bindingType &&
		       lhs.bitIndex == rhs.bitIndex &&
		       lhs.flags == rhs.flags &&
		       lhs.memberClass == rhs.memberClass &&
		       lhs.memberType == rhs.memberType &&
		       lhs.offsetInArrayPlusOne == rhs.offsetInArrayPlusOne &&
		       lhs.offsetInObjectPlusOne == rhs.offsetInObjectPlusOne;
	}
}
