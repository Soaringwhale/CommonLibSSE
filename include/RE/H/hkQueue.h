#pragma once

namespace RE
{
	/// A FIFO circular queue
	template <typename T>
	class hkQueue
	{
	public:
		hkQueue() = default;

		// members
		T*      data{ nullptr };  // 00
		int32_t capacity{};       // 08
		int32_t head{};           // 0C
		int32_t tail{};           // 10
		int32_t elementsInUse{};  // 14
	};
	// static_assert(sizeof(hkQueue<void*>) == 0x18);
}
