#pragma once

namespace RE
{
	class hkbBehaviorGraph;
	class hkbNode;

	class hkbGeneratorSyncInfo
	{
	public:
		/// The description of a point on the timeline that is used for synchronization.
		struct SyncPoint
		{
			// This must be trivial, as it is called from the finish constructor
			SyncPoint() = default;

			// Actually init the SyncPoint
			void init()
			{
				externalEventId = INVALID_ID;
				time = 0.0f;
			}

			enum
			{
				INVALID_ID = -1,
				START_OF_GENERATOR_ID = -2
			};

			// members
			int32_t externalEventId;  // 00 - The id of the sync point.
			float   time;             // 04 - The point on the timeline where this sync point is.
		};

		/// Copy constructor copies everything but then clears the m_isMirrored flag.
		hkbGeneratorSyncInfo(const hkbGeneratorSyncInfo& syncInfo)
		{
			std::memcpy(this, &syncInfo, sizeof(hkbGeneratorSyncInfo));
			isMirrored = false;
		}

		/// Assignment copies everything but then clears the m_isMirrored flag.
		hkbGeneratorSyncInfo& operator=(const hkbGeneratorSyncInfo& syncInfo)
		{
			std::memcpy(this, &syncInfo, sizeof(hkbGeneratorSyncInfo));
			isMirrored = false;
			return *this;
		}

		// members
		SyncPoint syncPoints[8];  // 00
		float     duration;       // 40
		float     localTime;      // 44
		float     playbackSpeed;  // 48
		uint8_t   numSyncPoints;  // 4C
		bool      isCyclic;       // 4D
		bool      isMirrored;     // 4E
		bool      isAdditive;     // 4F
	};
	static_assert(sizeof(hkbGeneratorSyncInfo) == 0x50);

	/// Information about a node in a behavior graph.
	struct hkbNodeInfo
	{
		hkbGeneratorSyncInfo syncInfo;         // 00
		hkbNode*             nodeTemplate;     // 50
		hkbNode*             nodeClone;        // 58
		hkbBehaviorGraph*    behavior;         // 60
		int32_t              some_ind;         // 68
		int32_t              parents_count;    // 6C
		int32_t              childs_count;     // 70
		int32_t              first_child_ind;  // 74 - activeNodes[ activeNodesChildrenIndices[first_child_ind .. +childs_count] ] -- childs (when this's ind == parentInd_v2)
		int32_t              syncParentInd;    // 78 - when childinfo.syncToParent == syncToParent == true
		int32_t              parentInd;        // 7C - first visited parent->child
		int32_t              unk80;            // 80 - usually 0
		bool                 ignoreEvents;     // 84
		bool                 isGenerator;      // 85
		bool                 syncToParent;     // 86
		bool                 stopped;          // 87 - usually 0
		bool                 activated;        // 88
		bool                 use_some_ind;     // 89 - true <=> some_ind > 0
		char                 pad8A[6];         // 8A
	};
	static_assert(sizeof(hkbNodeInfo) == 0x90);
}
