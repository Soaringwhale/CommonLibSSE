#pragma once

#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTTuple.h"
#include "RE/I/IMovementControllerRegisterInterface.h"
#include "RE/M/MovementAgent.h"
#include "RE/M/MovementArbiter.h"

namespace RE
{
	class IMovementControllerDataTracker;
	class IMovementState;
	struct MovementControllerActiveSetDescription;
	struct MovementHandlerOutputDataLargeDelta;
	struct MovementHandlerOutputDataSmallDelta;

	class MovementControllerAI :
		public IMovementControllerRegisterInterface,  // 000
		public BSIntrusiveRefCounted                  // 008
	{
		template <typename T>
		class ActiveSmartPtr
		{
		public:
			ActiveSmartPtr(const BSTSmartPointer<T>& a_ptr, bool active) :
				ptr(a_ptr)
			{
				SetActive(active);
			}

			ActiveSmartPtr(const ActiveSmartPtr& other) :
				ptr(other.Qptr())
			{
				SetActive(other.QActive());
			}

			~ActiveSmartPtr()
			{
				clear();
			}

			void SetActive(bool val)
			{
				clear();
				*reinterpret_cast<uint64_t*>(&ptr) |= static_cast<uint64_t>(val);
			}

			bool QActive() const
			{
				return *reinterpret_cast<const uint64_t*>(&ptr) & 1;
			}

			BSTSmartPointer<T> Qptr() const
			{
				auto ptr1 = reinterpret_cast<const uint64_t*>(&ptr);
				auto tmp1 = *ptr1 & static_cast<uint64_t>(-2);
				return *reinterpret_cast<BSTSmartPointer<T>*>(&tmp1);
			}

		private:
			void clear()
			{
				*reinterpret_cast<uint64_t*>(&ptr) &= static_cast<uint64_t>(-2);
			}

			// members
			BSTSmartPointer<T> ptr;  // 00
		};

	public:
		inline static constexpr auto RTTI = RTTI_MovementControllerAI;

		using ActiveArbiterSmartPtr = ActiveSmartPtr<MovementArbiter>;
		static_assert(sizeof(ActiveArbiterSmartPtr) == 0x8);

		using ActiveAgentSmartPtr = ActiveSmartPtr<MovementAgent>;
		static_assert(sizeof(ActiveAgentSmartPtr) == 0x8);

		static bool FindAgentByNameFunctor(const MovementAgent* agent, const BSFixedString& type);

		~MovementControllerAI() override;  // 00

		// add
		virtual IMovementState* QCurrentState();                                                          // 05
		virtual void            Init();                                                                   // 06 - { return; }
		virtual void            UpdateSmallDelta(float delta, MovementHandlerOutputDataSmallDelta& out);  // 07
		virtual void            UpdateLargeDelta(float delta, MovementHandlerOutputDataLargeDelta& out);  // 08
		virtual bool            PreUpdateSmallDelta(void);                                                // 09 - { return 1; }

		bool ActivateSet(const MovementControllerActiveSetDescription& set);

		bool GetMovementAgent(const BSFixedString& type, MovementAgentPtr& ans) const;

		// members
		BSTSmallArray<ActiveArbiterSmartPtr, 2>                         arbiters;     // 10
		BSTSmallArray<ActiveAgentSmartPtr, 1>                           agents;       // 30
		BSTSmallArray<BSTTuple<BSFixedString, IMovementInterface*>, 11> interfaces;   // 048
		BSSpinLock                                                      lock;         // 108
		FormID                                                          formID;       // 110
		char                                                            pad114[4];    // 114
		IMovementControllerDataTracker*                                 dataTracker;  // 118
	};
	static_assert(sizeof(MovementControllerAI) == 0x120);
}
