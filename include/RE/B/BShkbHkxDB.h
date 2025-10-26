#pragma once

#include "RE/A/AnimationFileManagerSingleton.h"
#include "RE/B/BSFixedString.h"
#include "RE/B/BSResourceEntryDB.h"
#include "RE/B/BSResourceHandle.h"
#include "RE/B/BSTHashMap.h"
#include "RE/H/hkLoader.h"

namespace RE
{
	class hkRootLevelContainer;
	class hkbAnimationBindingSet;
	class hkbProjectData;
	class hkbSymbolIdMap;

	namespace BShkbHkxDB
	{
		class ProjectDBData;
		class Stream;

		class DBData : public hkLoader
		{
		public:
			inline static constexpr auto RTTI = RTTI_BShkbHkxDB__DBData;
			inline static constexpr auto VTABLE = VTABLE_BShkbHkxDB__DBData;

			~DBData() override;  // 00

			// add
			virtual ProjectDBData* QProjectData();  // 0B
			virtual void           Unk_0C(void);    // 0C
			virtual void           LoadImpl(Stream** stream);
			virtual void           Unk_0E(void);  // 0E

			hkRootLevelContainer* root;  // 20
		};
		static_assert(sizeof(DBData) == 0x28);

		class ProjectDBData : public DBData
		{
		public:
			inline static constexpr auto RTTI = RTTI_BShkbHkxDB__ProjectDBData;
			inline static constexpr auto VTABLE = VTABLE_BShkbHkxDB__ProjectDBData;

			struct HashedData
			{
				// members
				AnimationFileManagerSingleton::AnimationFileInfo animationFileInfo;  // 00
				uint32_t                                         unkC;               // 0C
				void*                                            entry;              // 10
				void*                                            entryDB;            // 18
			};
			static_assert(sizeof(HashedData) == 0x20);

			struct InitData
			{
				BSTArray<hkbHkxDBHandle>*           hashedBehaviors;             // 00
				BSTArray<HashedData>*               hashedAnimations;            // 08
				void*                               ptr_field_58;                // 10
				BSTHashMap<BSFixedString, int32_t>* variableNamesToId;           // 18
				BSTHashMap<BSFixedString, int32_t>* eventNamesToIds;             // 20
				BSTArray<BSFixedString>*            eventNames;                  // 28
				BSTArray<BSFixedString>*            stateNames;                  // 30
				BSTSet<BSFixedString>*              synchronizedClipGenerators;  // 38
				BSTArray<uint8_t>*                  array;                       // 40
				void**                              speedSamplerMngr_data;       // 48 - ptr to ProjectDBData::speedSamplerMngr_data
				hkRefPtr<hkbAnimationBindingSet>*   animationBindingSet;         // 50
				hkRefPtr<hkbSymbolIdMap>*           characterPropertyIdMap;      // 58
				hkRefVariant*                       p_field170;                  // 60
				hkRefVariant*                       p_field178;                  // 68
			};
			static_assert(sizeof(InitData) == 0x70);

			~ProjectDBData() override;  // 00

			// override (DBData)
			ProjectDBData* QProjectData() override { return this; }  // 0B

			bool BeginInit(InitData& initData)
			{
				using func_t = decltype(&ProjectDBData::BeginInit);
				REL::Relocation<func_t> func{ RELOCATION_ID(62514, 63455) };
				return func(this, initData);
			}

			void EndInit()
			{
				using func_t = decltype(&ProjectDBData::EndInit);
				REL::Relocation<func_t> func{ RELOCATION_ID(62515, 63456) };
				return func(this);
			}

			BSTArray<hkbHkxDBHandle>           hashedBehaviors;             // 028
			BSTArray<HashedData>               hashedAnimations;            // 040
			void*                              unk58;                       // 058
			uint64_t                           unk60;                       // 060
			uint32_t                           unk68;                       // 068 - mb size of data from field_58
			uint32_t                           unk6C;                       // 06C
			BSTHashMap<BSFixedString, int32_t> variableNamesToId;           // 070
			BSTHashMap<BSFixedString, int32_t> eventNamesToIds;             // 0A0
			BSTArray<BSFixedString>            eventNames;                  // 0D0
			BSTArray<BSFixedString>            stateNames;                  // 0E8
			BSTSet<BSFixedString>              synchronizedClipGenerators;  // 100
			BSTArray<uint8_t>                  array;                       // 130
			void*                              speedSamplerMngr_data;       // 148 - BSSpeedSamplerDBManager::ProjectData *, refcounted
			hkRefPtr<hkbAnimationBindingSet>   animationBindingSet;         // 150
			hkRefPtr<hkbSymbolIdMap>           characterPropertyIdMap;      // 158
			hkRefPtr<hkbProjectData>           project_data;                // 160
			volatile int32_t                   state;                       // 168
			uint32_t                           unk16C;                      // 16C
			hkRefPtr<hkbCharacterSetup>        characterSetup;              // 170
			hkRefVariant                       unk178;                      // 178
		};
		static_assert(sizeof(ProjectDBData) == 0x180);

		struct DBTraits
		{
			inline static constexpr std::uint32_t LOAD_QUEUE_SIZE = 8;
			inline static constexpr std::uint32_t RELEASE_QUEUE_SIZE = 2;

			using U_Type = BShkbHkxDB::DBData*;

			static BSResource::EntryDB<DBTraits>& GetSingleton()
			{
				static REL::Relocation<BSResource::EntryDB<DBTraits>**> singleton{ RELOCATION_ID(516410, 402581) };
				return **singleton;
			}

			static void Release(BSResource::EntryDBBase<BSResource::EntryDBTraits<DBTraits, BSResource::EntryDB<DBTraits>>>& db, BSResource::Entry<BShkbHkxDB::DBData*, BSResource::EntryDBTraits<DBTraits, BSResource::EntryDB<DBTraits>>::CArgs>* entry)
			{
				using func_t = decltype(&DBTraits::Release);
				REL::Relocation<func_t> func{ RELOCATION_ID(31935, 0) };
				return func(db, entry);
			}
		};
	};
}
