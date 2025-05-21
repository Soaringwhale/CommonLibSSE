#pragma once

#include "RE/I/IMovementInterface.h"
#include "RE/M/MovementTweenerAgent.h"

namespace RE
{
	class ITweenerNodeFollowerSetup : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_ITweenerNodeFollowerSetup;
		inline static constexpr auto VTABLE = VTABLE_ITweenerNodeFollowerSetup;

		ITweenerNodeFollowerSetup() { stl::emplace_vtable(this); }

		virtual ~ITweenerNodeFollowerSetup() = default;  // 00

		// add
		virtual void SetFollowNode(const NiAVObjectPtr& node) = 0;  // 01
	};

	class MovementTweenerAgentNodeFollower : public MovementTweenerAgent, public ITweenerNodeFollowerSetup
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementTweenerAgentNodeFollower;
		inline static constexpr auto VTABLE = VTABLE_MovementTweenerAgentNodeFollower;

		MovementTweenerAgentNodeFollower() { stl::emplace_vtable(this); }

		~MovementTweenerAgentNodeFollower() override;  // 00

		// override (MovementAgent)
		const BSFixedString& GetAgentType() const override;                                                              // 01
		uint8_t              GetAgentSaveType() const override;                                                          // 02
		void                 RegisterWithController(IMovementControllerRegisterInterface& register_interface) override;  // 04
		void                 Activate() override;                                                                        // 06
		void                 UnregisterWithController() override;                                                        // 0A
		void                 SaveGame(BSPathingStreamWrite& stream) override;                                            // 0B
		void                 LoadGame(BSPathingStreamRead& stream) override;                                             // 0C

		// override (IMovementTweenerAgent)
		void Update(MovementHandlerOutputDataSmallDelta& handler_output_data, MovementTweenerAgentOutputData& tweener_output) override;  // 03

		// override (ITweenerNodeFollowerSetup)
		void SetFollowNode(const NiAVObjectPtr& node) override;  // 01

		// members
		IMovementControllerRegisterInterface* register_interface{ nullptr };  // 28
		FormID                                actorID{ 0 };                   // 30
		ActorHandle                           actorHandle;                    // 34
		NiAVObjectPtr                         node;                           // 38
		BSReadWriteLock                       lock;                           // 40
	};
	static_assert(sizeof(MovementTweenerAgentNodeFollower) == 0x48);
}
