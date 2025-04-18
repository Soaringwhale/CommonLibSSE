#pragma once

#include "RE/B/BSIntrusiveRefCounted.h"

namespace RE
{
	class BSPathingStreamRead;
	class BSPathingStreamWrite;
	class IMovementControllerRegisterInterface;
	struct MovementUpdateDataSmallDelta;
	struct MovementUpdateDataLargeDelta;

	BSSmartPointer(MovementArbiter);
	class MovementArbiter : public BSIntrusiveRefCounted
	{
	public:
		virtual ~MovementArbiter();  // 00

		virtual const BSFixedString&              GetPipelineStage() const;                                       // 01
		virtual const BSFixedString&              GetArbiterType() const;                                         // 02
		virtual uint8_t                           GetArbiterSaveType() const;                                     // 03
		virtual void                              RegisterWithController(IMovementControllerRegisterInterface&);  // 04
		virtual IMovementDebugRenderingInterface* GetDebugRenderingInterface();                                   // 05
		virtual void                              Activate();                                                     // 06
		virtual void                              Init(BSPathingStreamRead&);                                     // 07
		virtual void                              UpdateSmallDelta(MovementUpdateDataSmallDelta&);                // 08
		virtual void                              UpdateLargeDelta(MovementUpdateDataLargeDelta&);                // 09
		virtual void                              Kill();                                                         // 0A
		virtual void                              Deactivate();                                                   // 0B
		virtual void                              UnregisterWithController();                                     // 0C
		virtual void                              SaveGame(BSPathingStreamWrite&);                                // 0D
		virtual void                              LoadGame(BSPathingStreamRead&);                                 // 0E
		virtual bool                              AddAgent(const MovementAgentPtr&);                              // 0F
		virtual bool                              RemoveAgent(const MovementAgentPtr&);                           // 10
		virtual void                              RemoveAllAgents();                                              // 11

		// members
		IMovementState* movementState;  // 10
	};
	static_assert(sizeof(MovementArbiter) == 0x18);
}
