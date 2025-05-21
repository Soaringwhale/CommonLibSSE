#pragma once

#include "RE/I/IBSTCreator.h"

namespace RE
{
	template <class Derived, class Parent>
	struct BSTDerivedCreator : public IBSTCreator<Parent>
	{
	public:
		BSTDerivedCreator() = default;

		virtual ~BSTDerivedCreator() = default;  // 00

		// override (IBSTCreator<Parent>)
		// 01
		Parent* Create() const override
		{
			return new Derived();
		}

		// 02
		void Destroy(const Parent* a_val) const override
		{
			delete a_val;
		}
	};
}
