#pragma once

#include "RE/I/IPackageData.h"

namespace RE
{
	template <class Parent>
	class BGSNamedPackageData : public Parent
	{
	public:
		static_assert(std::is_base_of<IPackageData, Parent>::value);

		union Data
		{
			bool          b;
			std::uint32_t i;
			float         f;
			void*         p;
		};
		static_assert(sizeof(Data) == 0x8);

		~BGSNamedPackageData() override;  // 00 

		// override (IPackageData)
		void InitItem(TESForm* a_form) override;                    // 01 - { return; }
		void Load(TESFile* a_mod) override;                         // 02
		void Copy(const IPackageData* a_other) override;            // 03 - { return; }
		bool Compare(const IPackageData* a_other) const override;   // 04

	private:
		// members
		BSFixedString data;  // ??
	};
}
