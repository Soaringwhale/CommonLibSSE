#pragma once

#include "RE/B/BSPathingStreamWrite.h"

namespace RE
{
	class BSPathingStreamSimpleBufferWrite : public BSPathingStreamWrite
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPathingStreamSimpleBufferWrite;
		inline static constexpr auto VTABLE = VTABLE_BSPathingStreamSimpleBufferWrite;

		template <size_t N>
		BSPathingStreamSimpleBufferWrite(char (&data)[N]) :
			start(data), cur(data), size(N)
		{
			stl::emplace_vtable(this);
		}

		// override (BSPathingStreamWrite)
		bool DoWrite0(const BSFixedString& val) override;        // 00
		bool DoWrite1(float val) override;                       // 01
		bool DoWrite2(uint64_t val) override;                    // 02
		bool DoWrite3(int64_t val) override;                     // 03
		bool DoWrite4(uint32_t val) override;                    // 04
		bool DoWrite5(int32_t val) override;                     // 05
		bool DoWrite6(uint16_t val) override;                    // 06
		bool DoWrite7(int16_t val) override;                     // 07
		bool DoWrite8(uint8_t val) override;                     // 08
		bool DoWrite9(int8_t val) override;                      // 09
		bool DoWriteA(bool val) override;                        // 0A
		bool DoWriteNumericID(uint32_t val) override;            // 0B
		~BSPathingStreamSimpleBufferWrite() override = default;  // 0F
		uint32_t GetType() const override;                       // 10

		// members
		char*    start;     // 08
		char*    cur;       // 10
		uint32_t size;      // 18
		uint8_t  pad1C[4];  // 1C
	};
	static_assert(sizeof(BSPathingStreamSimpleBufferWrite) == 0x20);
}
