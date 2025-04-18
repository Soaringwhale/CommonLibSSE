#pragma once

namespace RE
{
	struct MovementControllerActiveSetDescription
	{
	public:
		struct Description
		{
			// members
			BSFixedString type;            // 00
			BSFixedString interface_name;  // 08
			const char*   description;     // 10
			uint32_t      size;            // 18
			uint32_t      pad1C;           // 1C
		};
		static_assert(sizeof(Description) == 0x20);

		// members
		BSTSmallArray<Description, 8>  arbiters;  // 000
		BSTSmallArray<Description, 32> agents;    // 110
	};
	static_assert(sizeof(MovementControllerActiveSetDescription) == 0x520);
}
