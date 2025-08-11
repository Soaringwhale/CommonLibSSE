#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkStringPtr.h"

namespace RE
{
	class hkbEventPayload : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbEventPayload;

		~hkbEventPayload() override;  // 00
	};
	static_assert(sizeof(hkbEventPayload) == 0x10);

	class hkbRealEventPayload : public hkbEventPayload
	{
	public:
		~hkbRealEventPayload() override;  // 00

		// members
		float   val;       // 10
		uint8_t pad14[4];  // 14
	};
	static_assert(sizeof(hkbRealEventPayload) == 0x18);

	class hkbIntEventPayload : public hkbEventPayload
	{
	public:
		~hkbIntEventPayload() override;  // 00

		// members
		int32_t val;       // 10
		uint8_t pad14[4];  // 14
	};
	static_assert(sizeof(hkbIntEventPayload) == 0x18);

	class hkbStringEventPayload : public hkbEventPayload
	{
	public:
		static const hkClass& staticClass()
		{
			return *REL::Relocation<hkClass*>(RELOCATION_ID(521145, 407663));
		}

		~hkbStringEventPayload() override;       // 00
		hkClass* GetClassType() const override;  // 01

		// members
		hkStringPtr string;  // 10
	};
	static_assert(sizeof(hkbStringEventPayload) == 0x18);

	class hkbNamedEventPayload : public hkbEventPayload
	{
	public:
		~hkbNamedEventPayload() override;  // 00

		// members
		hkStringPtr name;  // 10
	};
	static_assert(sizeof(hkbNamedEventPayload) == 0x18);

	class hkbNamedRealEventPayload : public hkbNamedEventPayload
	{
	public:
		~hkbNamedRealEventPayload() override;  // 00

		// members
		float   val;       // 18
		uint8_t pad1C[4];  // 1C
	};
	static_assert(sizeof(hkbNamedRealEventPayload) == 0x20);

	class hkbNamedIntEventPayload : public hkbNamedEventPayload
	{
	public:
		~hkbNamedIntEventPayload() override;  // 00

		// members
		int32_t val;       // 18
		uint8_t pad1C[4];  // 1C
	};
	static_assert(sizeof(hkbNamedIntEventPayload) == 0x20);

	class hkbNamedStringEventPayload : public hkbNamedEventPayload
	{
	public:
		~hkbNamedStringEventPayload() override;  // 00

		// members
		hkStringPtr data;  // 18
	};
	static_assert(sizeof(hkbNamedStringEventPayload) == 0x20);

	class hkbEventPayloadList : public hkbEventPayload
	{
	public:
		~hkbEventPayloadList() override;  // 00

		// members
		hkArray<hkbEventPayload*> payloads;  // 10
	};
	static_assert(sizeof(hkbEventPayloadList) == 0x20);
}
