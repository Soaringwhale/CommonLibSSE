#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"
#include "RE/M/MovementControllerActiveSetDescription.h"

namespace RE
{
	struct MovementControllerLoadedSetDescription
	{
		// members
		BSTSmallArray<BSFixedString, 8>  arbiters;  // 00
		BSTSmallArray<BSFixedString, 32> agents;    // 50
	};
	static_assert(sizeof(MovementControllerLoadedSetDescription) == 0x160);

	class LoadedSetForHighActorDescription : public MovementControllerLoadedSetDescription
	{
	public:
	};
	static_assert(sizeof(LoadedSetForHighActorDescription) == 0x160);

	class LoadedSetForHighActorWithFlightDescription : public MovementControllerLoadedSetDescription
	{
	public:
	};
	static_assert(sizeof(LoadedSetForHighActorWithFlightDescription) == 0x160);

	class LoadedSetForLowActorDescription : public MovementControllerLoadedSetDescription
	{
	public:
	};
	static_assert(sizeof(LoadedSetForLowActorDescription) == 0x160);

	class LoadedSetForLowActorWithFlightDescription : public MovementControllerLoadedSetDescription
	{
	public:
	};
	static_assert(sizeof(LoadedSetForLowActorWithFlightDescription) == 0x160);

	class ActiveSetForMotionDrivenActorDescription : public MovementControllerActiveSetDescription
	{
	public:
		// members
		char data1[256];  // 520
		char data2[8];    // 620
		char data3[8];    // 628
		char data4[8];    // 630
		char data5[8];    // 638
	};
	static_assert(sizeof(ActiveSetForMotionDrivenActorDescription) == 0x640);

	class ActiveSetForMotionDrivenFlightActorDescription : public MovementControllerActiveSetDescription
	{
	public:
		// members
		char data1[256];  // 520
	};
	static_assert(sizeof(ActiveSetForMotionDrivenFlightActorDescription) == 0x620);

	class ActiveSetForGraphDrivenAnimationDrivenFixedDeltaTweenerActorDescription : public MovementControllerActiveSetDescription
	{
	public:
		// members
		char data1[256];  // 520
		char data2[8];    // 620
		char data3[8];    // 628
		char data4[8];    // 630
	};
	static_assert(sizeof(ActiveSetForGraphDrivenAnimationDrivenFixedDeltaTweenerActorDescription) == 0x638);

	class ActiveSetForGraphDrivenAnimationDrivenActorWithControlsDescription : public MovementControllerActiveSetDescription
	{
	public:
		// members
		char data1[256];  // 520
		char data2[8];    // 620
	};
	static_assert(sizeof(ActiveSetForGraphDrivenAnimationDrivenActorWithControlsDescription) == 0x628);

	class ActiveSetForNodeFollowingActorDescription : public MovementControllerActiveSetDescription
	{
	public:
		// members
		char data1[256];  // 520
	};
	static_assert(sizeof(ActiveSetForNodeFollowingActorDescription) == 0x620);

	class ActiveSetForDirectControlActorDescription : public MovementControllerActiveSetDescription
	{
	public:
		// members
		char data1[256];  // 520
	};
	static_assert(sizeof(ActiveSetForDirectControlActorDescription) == 0x620);

	class ActiveSetForPlannerDirectControlActorDescription : public MovementControllerActiveSetDescription
	{
	public:
		// members
		char data1[256];  // 520
		char data2[8];    // 620
	};
	static_assert(sizeof(ActiveSetForPlannerDirectControlActorDescription) == 0x628);

	class ActiveSetForMotionDrivenControlsActorDescription : public MovementControllerActiveSetDescription
	{
	public:
		static ActiveSetForMotionDrivenControlsActorDescription& GetSingleton()
		{
			return **REL::Relocation<ActiveSetForMotionDrivenControlsActorDescription**>(RELOCATION_ID(517147, 403680).address());
		}

		// members
		char data1[256];  // 520
		char data2[8];    // 620
	};
	static_assert(sizeof(ActiveSetForMotionDrivenControlsActorDescription) == 0x628);

	class ActiveSetForAnimationDrivenAllowPlannerRotationActorDescription : public MovementControllerActiveSetDescription
	{
	public:
		// members
		char data1[256];  // 520
		char data2[8];    // 620
		char data3[8];    // 628
		char data4[8];    // 630
		char data5[8];    // 638
	};
	static_assert(sizeof(ActiveSetForAnimationDrivenAllowPlannerRotationActorDescription) == 0x640);

	class ActiveSetForAnimationDrivenAllowControlsRotationActorDescription : public MovementControllerActiveSetDescription
	{
	public:
		// members
		char data1[256];  // 520
		char data2[8];    // 620
	};
	static_assert(sizeof(ActiveSetForAnimationDrivenAllowControlsRotationActorDescription) == 0x628);

	class ActiveSetForAnimationDrivenAllowDirectControlRotationActorDescription : public MovementControllerActiveSetDescription
	{
	public:
		// members
		char data1[256];  // 520
	};
	static_assert(sizeof(ActiveSetForAnimationDrivenAllowDirectControlRotationActorDescription) == 0x620);

	class ActiveSetForMotionDrivenLandLowActorDescription : public MovementControllerActiveSetDescription
	{
	public:
	};
	static_assert(sizeof(ActiveSetForMotionDrivenLandLowActorDescription) == 0x520);

	class ActiveSetForMotionDrivenFlightLowActorDescription : public MovementControllerActiveSetDescription
	{
	public:
	};
	static_assert(sizeof(ActiveSetForMotionDrivenFlightLowActorDescription) == 0x520);

	class ActiveSetForStaticPathDescription : public MovementControllerActiveSetDescription
	{
	public:
		// members
		char data1[256];  // 520
		char data2[8];    // 620
	};
	static_assert(sizeof(ActiveSetForStaticPathDescription) == 0x628);

	class ActiveSetForKeepOffsetDescription : public MovementControllerActiveSetDescription
	{
	public:
		// members
		char data1[256];  // 520
	};
	static_assert(sizeof(ActiveSetForKeepOffsetDescription) == 0x620);

	class ActiveSetForMotionDrivenControlsWithTweenerActorDescription : public MovementControllerActiveSetDescription
	{
	public:
		// members
		char data1[256];  // 520
		char data2[8];    // 620
	};
	static_assert(sizeof(ActiveSetForMotionDrivenControlsWithTweenerActorDescription) == 0x628);

	struct MovementControllerSetDescriptions
	{
		static MovementControllerSetDescriptions& GetSingleton()
		{
			return **REL::Relocation<MovementControllerSetDescriptions**>{ RELOCATION_ID(517056, 403564) };
		}

		// members
		uint64_t                                                                unk00;                                             // 00
		LoadedSetForHighActorDescription                                        loadedHighActor;                                   // 0008
		LoadedSetForHighActorWithFlightDescription                              loadedHighActorWithFlight;                         // 0168
		LoadedSetForLowActorDescription                                         loadedLowActor;                                    // 02C8
		LoadedSetForLowActorWithFlightDescription                               loadedLowActorWithFlight;                          // 0428
		ActiveSetForMotionDrivenActorDescription                                motionDrivenActor;                                 // 0588
		ActiveSetForMotionDrivenFlightActorDescription                          motionDrivenFlightActor;                           // 0BC8
		ActiveSetForGraphDrivenAnimationDrivenFixedDeltaTweenerActorDescription graphDrivenAnimationDrivenFixedDeltaTweenerActor;  // 11E8
		ActiveSetForGraphDrivenAnimationDrivenActorWithControlsDescription      graphDrivenAnimationDrivenActorWithControls;       // 1820
		ActiveSetForNodeFollowingActorDescription                               nodeFollowingActor;                                // 1E48
		ActiveSetForDirectControlActorDescription                               directControlActor;                                // 2468
		ActiveSetForPlannerDirectControlActorDescription                        plannerDirectControlActor;                         // 2A88
		ActiveSetForMotionDrivenControlsActorDescription                        motionDrivenControlsActor;                         // 30B0
		ActiveSetForAnimationDrivenAllowPlannerRotationActorDescription         animationDrivenAllowPlannerRotationActor;          // 36D8
		ActiveSetForAnimationDrivenAllowControlsRotationActorDescription        animationDrivenAllowControlsRotationActor;         // 3D18
		ActiveSetForAnimationDrivenAllowDirectControlRotationActorDescription   animationDrivenAllowDirectControlRotationActor;    // 4340
		ActiveSetForMotionDrivenLandLowActorDescription                         motionDrivenLandLowActor;                          // 4960
		ActiveSetForMotionDrivenFlightLowActorDescription                       motionDrivenFlightLow;                             // 4E80
		ActiveSetForStaticPathDescription                                       staticPath;                                        // 53A0
		ActiveSetForKeepOffsetDescription                                       keepOffset;                                        // 59C8
		ActiveSetForMotionDrivenControlsWithTweenerActorDescription             motionDrivenControlsWithTweenerActor;              // 5FE8
	};
	static_assert(sizeof(MovementControllerSetDescriptions) == 0x6610);
}
