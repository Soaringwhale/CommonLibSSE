#pragma once

namespace RE
{
	struct MovementControllerActiveSetDescription
	{
	public:
		struct Description
		{
			Description() = default;

			template <size_t N>
			Description(BSFixedString t, BSFixedString i, char const (&data)[N]) :
				type(std::move(t)), interface_name(std::move(i)), ptr(data), size(N)
			{}

			// members
			BSFixedString type;            // 00
			BSFixedString interface_name;  // 08
			const char*   ptr{};           // 10
			uint32_t      size{ 0 };       // 18
			uint8_t       pad1C[4];        // 1C
		};
		static_assert(sizeof(Description) == 0x20);

		// members
		BSTSmallArray<Description, 8>  arbiters;  // 000
		BSTSmallArray<Description, 32> agents;    // 110
	};
	static_assert(sizeof(MovementControllerActiveSetDescription) == 0x520);
}
