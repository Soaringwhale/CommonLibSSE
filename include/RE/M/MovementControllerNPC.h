#pragma once

#include "RE/I/IAnimationSetCallbackFunctor.h"
#include "RE/I/IMovementDirectControl.h"
#include "RE/I/IMovementMessageInterface.h"
#include "RE/I/IMovementMotionDrivenControl.h"
#include "RE/I/IMovementPlannerDirectControl.h"
#include "RE/I/IMovementSelectIdle.h"
#include "RE/M/MovementControllerAI.h"

namespace RE
{
	class MovementMessagePlayIdle;
	class MovementMessage;
	class OptWarpToMessage;

	class MovementControllerNPC :
		public MovementControllerAI,           // 000
		public IMovementMessageInterface,      // 120
		public IMovementMotionDrivenControl,   // 128
		public IMovementSelectIdle,            // 130
		public IMovementDirectControl,         // 138
		public IMovementPlannerDirectControl,  // 140
		public IAnimationSetCallbackFunctor    // 148
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementControllerNPC;

		enum class MOVEMENT_TYPE : uint32_t
		{
			AnimationDriven = 0x0,
			MotionDrivenControls = 0x1,
			MotionDrivenLand = 0x2,
			MotionDrivenFlight = 0x3,
			AnimationDrivenAllowPlannerRotation = 0x4,
			AnimationDrivenAllowControlsRotation = 0x5,
			NodeFollowing = 0x6,
			MOVEMENT_TYPE_7 = 0x7,
			MOVEMENT_TYPE_8 = 0x8,
			MOVEMENT_TYPE_9 = 0x9,
			MotionDrivenLandLow = 0xA,
			MotionDrivenFlightLow = 0xB,
			MOVEMENT_TYPE_c = 0xC,
			StaticPathing = 0xD,
			MotionDrivenControlsWithTweener = 0xE,
		};

		~MovementControllerNPC() override;  // 00

		// add
		virtual void SetSprinting(bool val);     // 0A
		virtual bool GetSprinting() const;       // 0B
		virtual void SetAIDriven();              // 0C
		virtual void SetControlsDriven();        // 0D
		virtual bool GetAIDriven() const;        // 0E - { return unk1C5 == 0; }
		virtual bool GetControlsDriven() const;  // 0F - { return unk1C5; }
		virtual void SetNodeFollowing();         // 10
		virtual void SetFlying(bool val);        // 11
		virtual void SaveGame(void);             // 12
		virtual void LoadGame(void);             // 13
		virtual void Unk_14(void);               // 14

		// members
		BSSpinLock                 lock1;                 // 150
		BSTArray<MovementMessage*> messages;              // 158
		BSTArray<OptWarpToMessage> array2;                // 170
		BSTArray<void*>            array3;                // 188
		BSSpinLock                 lock2;                 // 1A0
		std::uint64_t              unk1A8;                // 1A8
		MovementMessagePlayIdle*   message_playIdle;      // 1B0
		Actor*                     actor;                 // 1B8
		MOVEMENT_TYPE              movement_type;         // 1C0
		bool                       mb_fly;                // 1C4
		bool                       controlsDriven;        // 1C5
		bool                       direct_control;        // 1C6
		bool                       plannerDirectControl;  // 1C7
		uint8_t                    field_1C8;             // 1C8
		uint8_t                    field_1C9;             // 1C9
		uint8_t                    StaticPathingState;    // 1CA
		uint8_t                    field_1CB;             // 1CB
		std::uint32_t              unk1CC;                // 1CC
	};
	static_assert(sizeof(MovementControllerNPC) == 0x1D0);
}
