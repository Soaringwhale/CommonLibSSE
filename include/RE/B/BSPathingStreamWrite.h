#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSPathingStream.h"
#include "RE/B/BSTArray.h"

namespace RE
{
	class BSPathingStreamWrite
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPathingStreamWrite;
		inline static constexpr auto VTABLE = VTABLE_BSPathingStreamWrite;

		template <typename T>
		bool Write(const T& val);

		// add
		virtual bool DoWrite0(const BSFixedString& val) = 0;         // 00
		virtual bool DoWrite1(float val) = 0;                        // 01
		virtual bool DoWrite2(uint64_t val) = 0;                     // 02
		virtual bool DoWrite3(int64_t val) = 0;                      // 03
		virtual bool DoWrite4(uint32_t val) = 0;                     // 04
		virtual bool DoWrite5(int32_t val) = 0;                      // 05
		virtual bool DoWrite6(uint16_t val) = 0;                     // 06
		virtual bool DoWrite7(int16_t val) = 0;                      // 07
		virtual bool DoWrite8(uint8_t val) = 0;                      // 08
		virtual bool DoWrite9(int8_t val) = 0;                       // 09
		virtual bool DoWriteA(bool val) = 0;                         // 0A
		virtual bool DoWriteNumericID(uint32_t val) = 0;             // 0B
		virtual bool DoWritePathingRequest(void) { return false; }   // 0C
		virtual bool DoWritePathingSolution(void) { return false; }  // 0D
		virtual bool DoWritePlayIdleResult(void) { return false; }   // 0E
		virtual ~BSPathingStreamWrite() = default;                   // 0F
		virtual uint32_t GetType() const = 0;                        // 10
	};
	static_assert(sizeof(BSPathingStreamWrite) == 0x8);

	namespace BSPathingStream
	{
		template <typename T>
		struct Trait;

		template <typename T, typename Alloc>
		struct Trait<BSTArray<T, Alloc>>
		{
			static bool Write(BSPathingStreamWrite& stream, const BSTArray<T, Alloc>& arr)
			{
				stream.DoWrite4(arr.size());
				for (const auto& i : arr) {
					stream.Write(i);
				}
				return true;
			}
		};

		template <>
		struct Trait<BSFixedString>
		{
			static bool Write(BSPathingStreamWrite& stream, const BSFixedString& val)
			{
				return stream.DoWrite0(val);
			}
		};
	}

	template <typename T>
	inline bool BSPathingStreamWrite::Write(const T& val)
	{
		return BSPathingStream::Trait<T>::Write(*this, val);
	}
}
