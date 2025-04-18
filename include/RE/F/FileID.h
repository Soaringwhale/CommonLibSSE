#pragma once

namespace RE
{
	namespace BSResource
	{
		struct FileID
		{
		public:
			// members
			std::uint32_t file;    // 00
			char          ext[4];  // 04
		};
		static_assert(sizeof(FileID) == 0x8);
	}
}
