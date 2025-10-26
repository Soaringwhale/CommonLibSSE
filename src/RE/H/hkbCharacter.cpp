#include "RE/H/hkbCharacter.h"

#include "RE/H/hkQsTransform.h"
#include "RE/H/hkaSkeleton.h"
#include "RE/H/hkbBehaviorGraph.h"
#include "RE/H/hkbCharacterSetup.h"
#include "RE/H/hkbEventQueue.h"
#include "RE/H/hkbProjectData.h"
#include "RE/H/hkbRagdollDriver.h"

namespace RE
{
	// TODO: implement dtor and move to the separate header
	class hkbHandIkDriver : public hkReferencedObject
	{
	public:
		hkArray<void*> array;     // 10 - elements contain hkReferencedObject*, need to free them
		uint8_t        field_20;  // 20
		uint8_t        pad21[7];  // 21
	};
	static_assert(sizeof(hkbHandIkDriver) == 0x28);

	// TODO: implement dtor and move to the separate header
	class hkbFootIkDriver : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbFootIkDriver;
		inline static constexpr auto VTABLE = VTABLE_hkbFootIkDriver;

		hkbFootIkDriver()
		{
			stl::emplace_vtable(this);
		}

		~hkbFootIkDriver() override = default;  // 00

		// members
		hkArray<void*> array;                       // 10 - elements contain hkReferencedObject*, need to free them
		hkVector4      field_20{};                  // 20
		hkQuaternion   field_30{ { 0, 0, 0, 1 } };  // 30
		uint64_t       field_40{ 0 };               // 40
		uint16_t       field48{ 0 };                // 48
		uint8_t        field4A{ 0 };                // 4A
		uint8_t        pad4B;                       // 4B
		float          field_4C{ 0 };               // 4C
	};
	static_assert(sizeof(hkbFootIkDriver) == 0x50);

	// TODO: implement. now don't create hkbRagdollDriver, hkbFootIkDriver, hkbHandIkDriver, eventQueue, worldFromModel
	hkbCharacter::hkbCharacter() :
		ragdollDriver(make_hkref<hkbRagdollDriver>(this, true)), footIkDriver(make_hkref<hkbFootIkDriver>()), handIkDriver(make_hkref<hkbHandIkDriver>()), eventQueue(new hkbEventQueue())
	{
		stl::emplace_vtable(this);
	}

	// TODO: implement. Now don't free eventQueue, PoseLocal, WorldFromModel
	hkbCharacter::~hkbCharacter()
	{
	}

	void hkbCharacter::getNearbyRigidBodies(const hkVector4& sensorPosWS, float maxDistance, void* a_world, hkArray<hkpRigidBody*>& rigidBodies, uint32_t collisionFilterInfo, bool excludeThisCharacter, bool inCharactersOnly)
	{
		using func_t = decltype(&hkbCharacter::getNearbyRigidBodies);
		REL::Relocation<func_t> func{ RELOCATION_ID(57878, 58451) };
		return func(this, sensorPosWS, maxDistance, a_world, rigidBodies, collisionFilterInfo, excludeThisCharacter, inCharactersOnly);
	}

	void hkbCharacter::getNearbyCharacters(float maxDistance, hkArray<hkbCharacter*>& characters)
	{
		using func_t = decltype(&hkbCharacter::getNearbyCharacters);
		REL::Relocation<func_t> func{ RELOCATION_ID(57879, 58452) };
		return func(this, maxDistance, characters);
	}

	void hkbCharacter::clearPoseLocal()
	{
		if (deletePoseLocal) {
			RE::hkMemoryRouter::easyFree(RE::hkMemoryRouter::getInstance().heap(), poseLocal);
			poseLocal = nullptr;
			deletePoseLocal = false;
		}
	}

	void hkbCharacter::setWorldFromModel(hkQsTransform* new_worldFromModel, bool new_deleteWorldFromModel)
	{
		if (deleteWorldFromModel && worldFromModel) {
			RE::hkMemoryRouter::getInstance().heap().BlockFree(worldFromModel, sizeof(hkQsTransform));
		}
		worldFromModel = new_worldFromModel;
		deleteWorldFromModel = new_deleteWorldFromModel;
	}

	void hkbCharacter::initPoseLocal()
	{
		if (!poseLocal) {
			auto& bones = setup->animationSkeleton->bones;
			numPoseLocal = bones.size();
			auto& router = hkMemoryRouter::getInstance();
			poseLocal = static_cast<hkQsTransform*>(hkMemoryRouter::easyAlloc(router.heap(), numPoseLocal * sizeof(hkQsTransform)));
			std::memcpy(poseLocal, bones.data(), numPoseLocal * sizeof(hkQsTransform));
			deletePoseLocal = true;
		}
	}

	hkQsTransform* hkbCharacter::getPoseLocal()
	{
		if (poseLocal)
			return poseLocal;

		initPoseLocal();
		return poseLocal;
	}

	hkbEventQueue* hkbCharacter::getEventQueue() const
	{
		return eventQueue;
	}
}
