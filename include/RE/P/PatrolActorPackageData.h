
#pragma once

#include "RE/A/ActorPackageData.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSPointerHandle.h"

namespace RE
{
	class PatrolActorPackageData : public ActorPackageData
	{
	public:
		inline static constexpr auto RTTI = RTTI_PatrolActorPackageData;
		
		~PatrolActorPackageData() override;                             // 00
		
		// override (ActorPackageData)
		std::uint32_t GetPackageType() override;                        // 01 - { return 13; }
		void          SaveGame(BGSSaveFormBuffer* a_buf) override;      // 05
		void          LoadGame(BGSLoadFormBuffer* a_buf) override;      // 06
		void          InitLoadGame(BGSLoadFormBuffer* a_buf) override;  // 07
		
		// members
		std::uint32_t             unk08;             // 08
		std::uint32_t             unk0C;             // 0C
		ActorHandle               ownerActorHandle;  // 10
		std::uint32_t             pad14;             // 14
		BSTArray<ObjectRefHandle> patrolPoints;      // 18
		std::uint32_t             unk30;             // 30
		bool                      unk34;             // 34
		bool                      unk35;             // 35
		std::uint16_t             pad36;             // 36
		std::uint32_t             currentPointIndex; // 38
		std::uint32_t             pad3C;             // 3C
	};
	static_assert(sizeof(PatrolActorPackageData) == 0x40);
}
