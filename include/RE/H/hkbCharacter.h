#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkQsTransform.h"
#include "RE/H/hkRefVariant.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkStringPtr.h"
#include "RE/H/hkaSkeleton.h"
#include "RE/H/hkbCharacterSetup.h"

namespace RE
{
	class hkbAnimationBindingSet;
	class hkbBehaviorGraph;
	class hkbCharacterSetup;
	class hkbEventQueue;
	class hkbProjectData;
	class hkbRagdollDriver;

	class hkbCharacter : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbCharacter;
		inline static constexpr auto VTABLE = VTABLE_hkbCharacter;

		~hkbCharacter() override;  // 00

		// add
		virtual void Unk_03(void);  // 03
		virtual void Unk_04(void);  // 04

		/// Get the event queue that stores events to be processed later by the character.
		hkbEventQueue* getEventQueue() const;

		void create_pose_local()
		{
			if (!poseLocal) {
				auto& bones = setup->animationSkeleton->bones;
				numPoseLocal = bones.size();
				auto& router = hkMemoryRouter::getInstance();
				poseLocal = static_cast<hkQsTransform*>(router.easyAlloc(router.heap(), numPoseLocal * sizeof(hkQsTransform)));
				std::memcpy(poseLocal, bones.data(), numPoseLocal * sizeof(hkQsTransform));
				deletePoseLocal = true;
			}
		}

		hkQsTransform* getPoseLocal()
		{
			if (poseLocal)
				return poseLocal;

			create_pose_local();

			return poseLocal;
		}

		// members
		hkArray<hkbCharacter*>           nearbyCharacters;           // 10
		std::int16_t                     currentLOD;                 // 20
		std::int16_t                     numTracksInLOD;             // 22
		std::uint32_t                    pad24;                      // 24
		hkStringPtr                      name;                       // 28
		hkRefPtr<hkbRagdollDriver>       ragdollDriver;              // 30
		hkRefVariant                     characterControllerDriver;  // 38
		hkRefVariant                     footIkDriver;               // 40
		hkRefVariant                     handIkDriver;               // 48
		hkRefPtr<hkbCharacterSetup>      setup;                      // 50 - The character rig and other shared data.
		hkRefPtr<hkbBehaviorGraph>       behaviorGraph;              // 58 - Behavior graph for the character
		hkRefPtr<hkbProjectData>         projectData;                // 60 - Project for the character
		hkRefPtr<hkbAnimationBindingSet> animationBindingSet;        // 68 - The animation binding set for this character if it is different from the one in m_setup that is shared among all the characters of this type.
		hkRefVariant                     raycastInterface;           // 70
		hkRefVariant                     world;                      // 78
		hkbEventQueue*                   eventQueue;                 // 80 - unique_ptr?
		hkRefVariant                     worldFromModel;             // 88
		hkQsTransform*                   poseLocal;                  // 90 - easy allocated
		std::int32_t                     numPoseLocal;               // 98
		bool                             deleteWorldFromModel;       // 9C
		bool                             deletePoseLocal;            // 9D
		std::uint16_t                    pad9E;                      // 9E
	};
	static_assert(sizeof(hkbCharacter) == 0xA0);
}
