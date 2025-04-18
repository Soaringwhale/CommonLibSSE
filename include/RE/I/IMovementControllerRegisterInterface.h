#pragma once

#include "RE/B/BSFixedString.h"

namespace RE
{
	struct IMovementInterface;

	class IMovementControllerRegisterInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementControllerRegisterInterface;

		virtual ~IMovementControllerRegisterInterface();  // 00

		// add
		virtual void                RegisterInterface(const BSFixedString& name, IMovementInterface* interface) = 0;  // 01
		virtual IMovementInterface* GetInterface1(const BSFixedString& name) = 0;                                     // 02
		virtual IMovementInterface* GetInterface2(const BSFixedString& name) = 0;                                     // 03
		virtual void                UnregisterInterface(const BSFixedString& name) = 0;                               // 04
	};
	static_assert(sizeof(IMovementControllerRegisterInterface) == 0x8);
}
