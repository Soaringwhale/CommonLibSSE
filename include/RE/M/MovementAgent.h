#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/I/IMovementInterface.h"
#include "RE/N/NiAVObject.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiTransform.h"

namespace RE
{
	class BSPathingStreamRead;
	class BSPathingStreamWrite;
	class IMovementDebugRenderingInterface;
	class IMovementState;
	struct IPipelineStageInterface;

	BSSmartPointer(MovementAgent);
	class MovementAgent : public BSIntrusiveRefCounted
	{
	public:
		virtual ~MovementAgent();  // 00

		virtual const BSFixedString&              GetAgentType() const = 0;                                       // 01
		virtual uint8_t                           GetAgentSaveType() const = 0;                                   // 02
		virtual IPipelineStageInterface*          GetPipelineStageInterface(const BSFixedString&) = 0;            // 03
		virtual void                              RegisterWithController(IMovementControllerRegisterInterface&);  // 04
		virtual IMovementDebugRenderingInterface* GetDebugRenderingInterface();                                   // 05
		virtual void                              Activate();                                                     // 06
		virtual void                              Init(BSPathingStreamRead&);                                     // 07
		virtual void                              Kill();                                                         // 08
		virtual void                              Deactivate();                                                   // 09
		virtual void                              UnregisterWithController();                                     // 0A
		virtual void                              SaveGame(BSPathingStreamWrite&);                                // 0B
		virtual void                              LoadGame(BSPathingStreamRead&);                                 // 0C

		// members
		IMovementState* movementState;  // 10
	};
	static_assert(sizeof(MovementAgent) == 0x18);

	class MovementPlannerAgentReturnDataSmallDelta;
	struct MovementPlannerUpdateDataSmallDelta;

	struct IPipelineStageInterface
	{
		virtual ~IPipelineStageInterface();  // 00
	};
	static_assert(sizeof(IPipelineStageInterface) == 0x8);

	struct IMovementPlannerAgent : public IPipelineStageInterface
	{
		virtual ~IMovementPlannerAgent();  // 00

		// add
		virtual const BSFixedString& GetPlannerAgentType() const;                                                                                                      // 01
		virtual void                 UpdateSmallDelta(const MovementPlannerUpdateDataSmallDelta& update_data, MovementPlannerAgentReturnDataSmallDelta& return_data);  // 02
		virtual void                 UpdateLargeDelta(void);                                                                                                           // 03
	};

	class MovementPlannerAgent : public MovementAgent, public IMovementPlannerAgent
	{
	public:
	};
	static_assert(sizeof(MovementPlannerAgent) == 0x20);

	class MovementPlannerAgentDirectControl : public MovementPlannerAgent
	{
	public:
		NiPoint3 GetTargetDirection() const
		{
			BSReadLockGuard g(lock);
			auto            ans = targetDirection;
			return ans;
		}

		float GetTargetSpeed() const
		{
			BSReadLockGuard g(lock);
			auto            ans = targetSpeed;
			return ans;
		}

		NiPoint3 GetTargetAngle() const
		{
			BSReadLockGuard g(lock);
			auto            ans = targetAngle;
			return ans;
		}

		// members
		IMovementControllerRegisterInterface* register_interface;  // 20
		mutable BSReadWriteLock               lock;                // 28
		NiPoint3                              targetDirection;     // 30
		float                                 targetSpeed;         // 3C
		NiPoint3                              targetAngle;         // 40
		char                                  pad4C[4];            // 4C
	};
	static_assert(sizeof(MovementPlannerAgentDirectControl) == 0x50);

	struct MovementHandlerOutputDataSmallDelta;
	struct MovementTweenerAgentOutputData
	{
		// members
		NiPoint3  P;  // 00
		NiMatrix3 M;  // 0C
	};
	static_assert(sizeof(MovementTweenerAgentOutputData) == 0x30);

	struct IMovementTweenerAgent : public IPipelineStageInterface
	{
		virtual ~IMovementTweenerAgent();  // 00

		// add
		virtual const BSFixedString& GetTweenerAgentType() const;                                                                                       // 01
		virtual void                 set_transform(const NiTransform& data, NiTransform& ans);                                                          // 02
		virtual void                 Update(MovementHandlerOutputDataSmallDelta& handler_output_data, MovementTweenerAgentOutputData& tweener_output);  // 03
	};

	class MovementTweenerAgent : public MovementAgent, public IMovementTweenerAgent
	{};
	static_assert(sizeof(MovementTweenerAgent) == 0x20);

	class ITweenerNodeFollowerSetup : public IMovementInterface
	{
	public:
		virtual ~ITweenerNodeFollowerSetup();  // 00

		virtual void SetFollowNode(const NiAVObjectPtr& node);  // 01
	};

	class MovementTweenerAgentNodeFollower : public MovementTweenerAgent, public ITweenerNodeFollowerSetup
	{
	public:
		// members
		IMovementControllerRegisterInterface* register_interface;  // 28
		RE::FormID                            actorID;             // 30
		ActorHandle                           actorHandle;         // 34
		NiAVObjectPtr                         node;                // 38
		BSReadWriteLock                       lock;
	};
	static_assert(sizeof(MovementTweenerAgentNodeFollower) == 0x48);
}
