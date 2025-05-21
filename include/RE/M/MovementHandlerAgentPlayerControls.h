#pragma once

#include "RE/B/BSTArray.h"
#include "RE/I/IMovementInterface.h"
#include "RE/M/MovementHandlerAgent.h"

namespace RE
{
	class IMovementControllerRegisterInterface;

	struct IMovementSetPlayerControls : public IMovementInterface
	{
		inline static constexpr auto RTTI = RTTI_IMovementSetPlayerControls;
		inline static constexpr auto VTABLE = VTABLE_IMovementSetPlayerControls;

		~IMovementSetPlayerControls() override = default;  // 00

		// add
		virtual void SetDampenAccelerationMultiplier(float val) = 0;        // 01
		virtual void SetFreezeDirectionOnLargeDeltaControls(bool val) = 0;  // 02
		virtual void set_input_type(int val) = 0;                           // 03 -- seems unused
	};
	static_assert(sizeof(IMovementSetPlayerControls) == 0x8);

	class MovementHandlerAgentPlayerControls : public MovementHandlerAgent, public IMovementSetPlayerControls
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementHandlerAgentPlayerControls;
		inline static constexpr auto VTABLE = VTABLE_MovementHandlerAgentPlayerControls;

		struct Data40
		{
			struct HeadingSpeedDtime
			{
				// members
				float heading{ 0 };  // 00
				float speed{ 0 };    // 04
				float dtime{ 0 };    // 08
			};
			static_assert(sizeof(HeadingSpeedDtime) == 0xC);

			struct Item
			{
				// members
				HeadingSpeedDtime hsd;         // 00
				uint8_t           flags{ 0 };  // 0C
				uint8_t           pad0D[3];
			};
			static_assert(sizeof(Item) == 0x10);

			struct struc_sub_1406FC780
			{
				// members
				float                      heading{ 0.0f };  // 00
				float                      speed{ 0.0f };    // 04
				BSTSmallArray<uint32_t, 4> flag_inds{};      // 08
			};
			static_assert(sizeof(struc_sub_1406FC780) == 0x28);

			Data40()
			{
				using func_t = Data40*(Data40*);
				REL::Relocation<func_t> func{ RELOCATION_ID(40945, 0) };
				func(this);
			}

			// members
			Item    data[32];              // 000
			int32_t ind1{ 0 };             // 200
			int32_t ind2{ 1 };             // 204
			int32_t ind3{ -1 };            // 208
			int32_t ind4{ -1 };            // 20C
			float   time{ 0 };             // 210
			bool    treshold_passed{ 0 };  // 214
			uint8_t pad215[3];             // 215
		};
		static_assert(sizeof(Data40) == 0x218);

		// members
		IMovementControllerRegisterInterface* register_interface;                    // 28
		uint64_t                              lock;                                  // 30
		uint32_t                              mb_input_type;                         // 38
		uint8_t                               pad3C[4];                              // 3C
		Data40*                               data40;                                // 40
		float                                 dampenAccelerationMultiplier;          // 48
		bool                                  bFreezeDirectionOnLargeDeltaControls;  // 4C
		uint8_t                               pad4D[3];                              // 4D
	};
	static_assert(sizeof(MovementHandlerAgentPlayerControls) == 0x50);
}
