#pragma once

#include "RE/B/BGSNamedPackageData.h"
#include "RE/B/BSFixedString.h"

namespace RE
{
	class TESFile;
	class BGSPackageDataValidationContext;

	template <class Parent, class Pointer /*, const BSFixedString& TYPE_NAME*/>
	class BGSPackageDataPointerTemplate : public BGSNamedPackageData<Parent>
	{
	public:
		virtual ~BGSPackageDataPointerTemplate();  // 00

		// override (BGSNamedPackageData<Parent>)
		void                               Validate(BGSPackageDataValidationContext& a_validationContext) override; // 05  -  { return 1; }
		[[nodiscard]] const BSFixedString& QType() const override;                                                  // 0B  -  { return TYPE_NAME; }

		// add
		//virtual void InternalLoad(TESFile* a_mod) = 0;  //

		// members
		Pointer* pointer;  // ??
	};
}
