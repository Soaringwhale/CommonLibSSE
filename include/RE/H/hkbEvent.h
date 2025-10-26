#pragma once

#include "RE/H/hkbEventBase.h"
#include "RE/H/hkbEventPayload.h"

namespace RE
{
	class hkbNode;

	/// A behavior event.
	/// An hkbEvent contains an integer ID and a payload.  Events can be sent to behavior nodes by the user,
	/// or sent by behavior nodes to each other or to the user.  This class does not reference count the payload.
	class hkbEvent : public hkbEventBase
	{
	public:
		// members
		hkbNode* sender{ nullptr };  // 10
	};
	static_assert(sizeof(hkbEvent) == 0x18);

	/// An event that is used as a node property. It differs from hkbEvent in that the payload is reference counted
	/// and it doesn't have a sender.
	class hkbEventProperty : public hkbEventBase
	{
	public:
		hkbEventProperty() = default;
		~hkbEventProperty()
		{
			setPayload(nullptr);
		}

		/// Set the event payload (user data) and add a reference.
		void setPayload(hkbEventPayload* a_payload)
		{
			if (a_payload) {
				a_payload->AddReference();
			}

			if (payload) {
				payload->RemoveReference();
			}

			payload = a_payload;
		}
	};
	static_assert(sizeof(hkbEventProperty) == 0x10);
}
