#pragma once

#include "RE/B/BSFixedString.h"

namespace RE
{
	class BSPathingStreamRead
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPathingStreamRead;
		inline static constexpr auto VTABLE = VTABLE_BSPathingStreamRead;

		// add
		virtual bool DoRead(BSFixedString& ans) = 0;                    // 00
		virtual bool DoRead(float& ans) = 0;                            // 01
		virtual bool DoRead(uint64_t& ans) = 0;                         // 02
		virtual bool DoRead(int64_t& ans) = 0;                          // 03
		virtual bool DoRead(uint32_t& ans) = 0;                         // 04
		virtual bool DoRead(int32_t& ans) = 0;                          // 05
		virtual bool DoRead(uint16_t& ans) = 0;                         // 06
		virtual bool DoRead(int16_t& ans) = 0;                          // 07
		virtual bool DoRead(uint8_t& ans) = 0;                          // 08
		virtual bool DoRead(int8_t& ans) = 0;                           // 09
		virtual bool DoRead(bool& ans) = 0;                             // 0A
		virtual bool DoReadNumericID(uint32_t& ans, bool& unused) = 0;  // 0B
		virtual bool DoReadNumericID(uint32_t& ans) = 0;                // 0C
		virtual bool DoReadPathingRequest(void) { return false; }       // 0D
		virtual bool DoReadPathingSolution(void) { return false; }      // 0E
		virtual bool DoReadPlayIdleResult(void) { return false; }       // 0F
		virtual ~BSPathingStreamRead() = default;                       // 10
		virtual uint32_t GetType() const = 0;                           // 11
		virtual uint32_t GetStaticDataVersionNumber() const = 0;        // 12
		virtual uint32_t GetDynamicDataVersionNumber() const = 0;       // 13
	};
	static_assert(sizeof(BSPathingStreamRead) == 0x8);
}
