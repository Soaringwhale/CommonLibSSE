#pragma once

namespace RE
{
	/// How to treat the world-from-model when using the powered ragdoll controller.
	struct hkbWorldFromModelModeData
	{
	public:
		/// How to compute the output worldFromModel when using the powered ragdoll controller.
		/// When using the rigid body ragdoll controller the input worldFromModel is always returned.
		enum class WorldFromModelMode : uint8_t
		{
			/// Return the previous worldFromModel of the character, ignoring the incoming worldFromModel.
			/// This causes the character's position and orientation to remain fixed while in ragdoll mode.
			WORLD_FROM_MODEL_MODE_USE_OLD,

			/// Return the worldFromModel that accompanies the input pose.  This usually only makes sense
			/// if you are keyframing some of the bones, because then the ragdoll tends to follow
			/// the motion in the animation.
			WORLD_FROM_MODEL_MODE_USE_INPUT,

			/// Compute the worldFromModel by matching the animation to the ragdoll.
			WORLD_FROM_MODEL_MODE_COMPUTE,

			/// Used to indicate that the mode should not be set.
			WORLD_FROM_MODEL_MODE_NONE,

			WORLD_FROM_MODEL_MODE_RAGDOLL
		};

		// members
		int16_t                                       poseMatchingBone0;  // 00 - A bone to use for pose matching used when computing the world-from-model for the ragdoll.
		int16_t                                       poseMatchingBone1;  // 02 - A bone to use for pose matching used when computing the world-from-model for the ragdoll.
		int16_t                                       poseMatchingBone2;  // 04 - A bone to use for pose matching used when computing the world-from-model for the ragdoll.
		stl::enumeration<WorldFromModelMode, uint8_t> mode;               // 06 - How to treat the world-from-model when using the powered ragdoll controller.
		uint8_t                                       pad7[1];            // 07
	};
	static_assert(sizeof(hkbWorldFromModelModeData) == 0x8);
}
