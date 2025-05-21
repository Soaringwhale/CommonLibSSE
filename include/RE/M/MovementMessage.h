#pragma once

#include "RE/B/BSTSmartPointer.h"

namespace RE
{
	class BSPathingStreamRead;
	class BSPathingStreamWrite;
	struct IPathFollowerAction;

	BSSmartPointer(MovementMessage);
	class MovementMessage : public BSIntrusiveRefCounted
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessage;
		inline static constexpr auto VTABLE = VTABLE_MovementMessage;

		virtual ~MovementMessage() = default;                                             // 00
		virtual uint32_t             GetType() const = 0;                                 // 01
		virtual void                 Write(BSPathingStreamWrite& stream) const = 0;       // 02
		virtual void                 Read(BSPathingStreamRead& stream) = 0;               // 03
		virtual void                 FixupNumericID(void*){};                             // 04
		virtual IPathFollowerAction* GetPathFollowerActionInterface(void) { return 0; };  // 05
	};
	static_assert(sizeof(MovementMessage) == 0x10);
}
