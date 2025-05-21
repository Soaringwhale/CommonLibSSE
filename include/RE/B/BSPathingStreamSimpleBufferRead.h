#pragma once

#include "RE/B/BSPathingStreamRead.h"

namespace RE
{
	class BSPathingStreamSimpleBufferRead : public BSPathingStreamRead
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPathingStreamSimpleBufferRead;
		inline static constexpr auto VTABLE = VTABLE_BSPathingStreamSimpleBufferRead;

		BSPathingStreamSimpleBufferRead(const char* data, uint32_t sz) :
			start(data), cur(data), size(sz)
		{
			stl::emplace_vtable(this);
		}

		// override (BSPathingStreamRead)
		bool DoRead(BSFixedString& ans) override;                    // 00
		bool DoRead(float& ans) override;                            // 01
		bool DoRead(uint64_t& ans) override;                         // 02
		bool DoRead(int64_t& ans) override;                          // 03
		bool DoRead(uint32_t& ans) override;                         // 04
		bool DoRead(int32_t& ans) override;                          // 05
		bool DoRead(uint16_t& ans) override;                         // 06
		bool DoRead(int16_t& ans) override;                          // 07
		bool DoRead(uint8_t& ans) override;                          // 08
		bool DoRead(int8_t& ans) override;                           // 09
		bool DoRead(bool& ans) override;                             // 0A
		bool DoReadNumericID(uint32_t& ans, bool& unused) override;  // 0B
		bool DoReadNumericID(uint32_t& ans) override;                // 0C
		~BSPathingStreamSimpleBufferRead() = default;                // 10
		uint32_t GetType() const override;                           // 11
		uint32_t GetStaticDataVersionNumber() const override;        // 12
		uint32_t GetDynamicDataVersionNumber() const override;       // 13

		// members
		const char* start;  // 08
		const char* cur;    // 10
		uint32_t    size;   // 18
		uint8_t     pad1C[4];
	};
	static_assert(sizeof(BSPathingStreamSimpleBufferRead) == 0x20);
}
