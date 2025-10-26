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
		Parent* CreateImpl() const override
		{
			return new Derived();
		}

		// 02
		void Destroy(const Parent* a_val) const override
		{
			delete a_val;
		}

		Derived* Create() const
		{
			return reinterpret_cast<Derived*>(CreateImpl());
		}
	};
}
