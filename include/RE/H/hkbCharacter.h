#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkRefVariant.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkStringPtr.h"

namespace RE
{
	class hkVector4;
	class hkQsTransform;
	class hkbAnimationBindingSet;
	class hkbBehaviorGraph;
	class hkbCharacterSetup;
	class hkbEventQueue;
	class hkbFootIkDriver;
	class hkbHandIkDriver;
	class hkbProjectData;
	class hkbRagdollDriver;
	class hkpRigidBody;

	class hkbCharacter : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbCharacter;
		inline static constexpr auto VTABLE = VTABLE_hkbCharacter;

		hkbCharacter();

		// 00
		~hkbCharacter() override;

		// add
		virtual void getNearbyRigidBodies(const hkVector4& sensorPosWS, float maxDistance, void* world, hkArray<hkpRigidBody*>& rigidBodies, uint32_t collisionFilterInfo, bool excludeThisCharacter, bool inCharactersOnly);  // 03

		// TODO: implement
		virtual void getNearbyCharacters(float maxDistance, hkArray<hkbCharacter*>& characters);  // 04

		void clearPoseLocal();
		/// Get the event queue that stores events to be processed later by the character.
		hkbEventQueue* getEventQueue() const;
		hkQsTransform* getPoseLocal();
		void           initPoseLocal();
		void           setWorldFromModel(hkQsTransform* new_worldFromModel, bool new_deleteWorldFromModel);

		// members
		hkArray<hkbCharacter*>           nearbyCharacters;               // 10
		int16_t                          currentLOD{ -1 };               // 20
		int16_t                          numTracksInLOD{ -1 };           // 22
		uint8_t                          pad24[4];                       // 24
		hkStringPtr                      name;                           // 28
		hkRefPtr<hkbRagdollDriver>       ragdollDriver;                  // 30
		hkRefVariant                     characterControllerDriver;      // 38
		hkRefPtr<hkbFootIkDriver>        footIkDriver;                   // 40
		hkRefPtr<hkbHandIkDriver>        handIkDriver;                   // 48
		hkRefPtr<hkbCharacterSetup>      setup;                          // 50 - The character rig and other shared data.
		hkRefPtr<hkbBehaviorGraph>       behaviorGraph;                  // 58 - Behavior graph for the character
		hkRefPtr<hkbProjectData>         projectData;                    // 60 - Project for the character
		hkRefPtr<hkbAnimationBindingSet> animationBindingSet;            // 68 - The animation binding set for this character if it is different from the one in m_setup that is shared among all the characters of this type.
		void*                            raycastInterface{};             // 70
		void*                            world{};                        // 78
		hkbEventQueue*                   eventQueue{};                   // 80 - unique_ptr?
		hkQsTransform*                   worldFromModel{};               // 88
		hkQsTransform*                   poseLocal{};                    // 90 - easy allocated
		int32_t                          numPoseLocal{};                 // 98
		bool                             deleteWorldFromModel{ false };  // 9C
		bool                             deletePoseLocal{ false };       // 9D
		uint8_t                          pad9E[2];                       // 9E
	};
	static_assert(sizeof(hkbCharacter) == 0xA0);
}
