#include "RE/H/hkClass.h"

namespace RE
{
	bool RE::hkClass::isSuperClass(const hkClass& k) const
	{
		for (const hkClass* clas = &k; clas; clas = clas->parent) {
			if (!std::strcmp(clas->name, name)) {
				return true;
			}
		}
		return false;
	}
}
