#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/I/IMovementInterface.h"
#include "RE/I/IPipelineStageInterface.h"
#include "RE/N/NiAVObject.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiTransform.h"

namespace RE
{
	class BSPathingStreamRead;
	class BSPathingStreamWrite;
	class IMovementControllerRegisterInterface;
	class IMovementDebugRenderingInterface;
	struct IMovementState;
	class MovementParameters;

	BSSmartPointer(MovementAgent);
	class MovementAgent : public BSIntrusiveRefCounted
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementAgent;
		inline static constexpr auto VTABLE = VTABLE_MovementAgent;

		MovementAgent();

		virtual ~MovementAgent() = default;  // 00

		// add
		virtual const BSFixedString&              GetAgentType() const = 0;                                                                             // 01
		virtual uint8_t                           GetAgentSaveType() const = 0;                                                                         // 02
		virtual IPipelineStageInterface*          GetPipelineStageInterface(const BSFixedString& stage) = 0;                                            // 03
		virtual void                              RegisterWithController([[maybe_unused]] IMovementControllerRegisterInterface& register_interface) {}  // 04
		virtual IMovementDebugRenderingInterface* GetDebugRenderingInterface() { return nullptr; }                                                      // 05
		virtual void                              Activate() {}                                                                                         // 06
		virtual void                              Init([[maybe_unused]] BSPathingStreamRead& stream) {}                                                 // 07
		virtual void                              Kill() {}                                                                                             // 08
		virtual void                              Deactivate() {}                                                                                       // 09
		virtual void                              UnregisterWithController() {}                                                                         // 0A
		virtual void                              SaveGame([[maybe_unused]] BSPathingStreamWrite& stream) {}                                            // 0B
		virtual void                              LoadGame([[maybe_unused]] BSPathingStreamRead& stream) {}                                             // 0C

		// members
		IMovementState* movementState;  // 10
	};
	static_assert(sizeof(MovementAgent) == 0x18);
}
