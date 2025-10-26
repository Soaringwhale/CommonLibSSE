#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkClass;
	class hkResource;
	class hkStreamReader;
	class hkTypeInfoRegistry;

	class hkLoader : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkLoader;
		inline static constexpr auto VTABLE = VTABLE_hkLoader;

		~hkLoader() override;  // 00

		// add
		virtual void* load_reader_class_registry(hkStreamReader* reader, hkClass* expectedTopLevelClass, hkTypeInfoRegistry* finish);  // 03
		virtual void* load_filename_class_registry(const char* filename, hkClass* expectedTopLevelClass, hkTypeInfoRegistry* finish);  // 04
		virtual void* load_reader_class(hkStreamReader* reader, hkClass* expectedTopLevelClass);                                       // 05
		virtual void* load_filename_class(const char* filename, hkClass* expectedTopLevelClass);                                       // 06
		virtual void* load_reader_registry(hkStreamReader* reader, hkTypeInfoRegistry* finish);                                        // 07
		virtual void* load_filename_registry(char* filename, hkTypeInfoRegistry* finish);                                              // 08
		virtual void* load_reader(hkStreamReader* reader);                                                                             // 09
		virtual void* load_filename(const char* filename);                                                                             // 0A

		// members
		hkArray<hkResource> loadedData;  // 08
	};
	static_assert(sizeof(hkLoader) == 0x20);
}
