#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkStringPtr.h"

namespace RE
{
	class hkClass;
	class hkRefVariant;
	class hkbBindableCollector;

	class hkbVariableBindingSet : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbVariableBindingSet;
		inline static constexpr auto VTABLE = VTABLE_hkbVariableBindingSet;

		struct Binding
		{
		public:
			/// Which data we are binding to.
			enum class BindingType : uint8_t
			{
				/// Binding to a variable.
				BINDING_TYPE_VARIABLE,

				/// Binding to a character property.
				BINDING_TYPE_CHARACTER_PROPERTY,
			};

			enum class Flags : uint8_t
			{
				FLAG_NONE = 0,

				// values are copied from the property to bound variables
				FLAG_OUTPUT = 1,
			};

			Binding() = default;
			Binding(const char* memberPath, int32_t variableIndex, BindingType bindingType, int8_t bitIndex);

			bool isOutput() const { return flags.all(Flags::FLAG_OUTPUT); };

			// members
			hkStringPtr                      memberPath;                                         // 00
			hkClass*                         memberClass{ nullptr };                             // 08
			int32_t                          offsetInObjectPlusOne{ 0 };                         // 10
			int32_t                          offsetInArrayPlusOne{ 0 };                          // 14
			int32_t                          rootVariableIndex{ -1 };                            // 18
			int32_t                          variableIndex{ 0 };                                 // 1C
			int8_t                           bitIndex{ -1 };                                     // 20
			BindingType                      bindingType{ BindingType::BINDING_TYPE_VARIABLE };  // 21
			int8_t                           memberType{ 0 };                                    // 22
			int8_t                           variableType{ -1 };                                 // 23
			stl::enumeration<Flags, uint8_t> flags{};                                            // 24
			char                             pad25[3];                                           // 25
		};
		static_assert(sizeof(Binding) == 0x28);

		hkbVariableBindingSet() { stl::emplace_vtable(this); }
		~hkbVariableBindingSet() override = default;  // 00

		/// Add a binding to the set.
		///
		/// The memberPath is made up of member names, separated by '/'.
		/// Integers after colons in the path are array indices.
		/// For example, "children:2/blendWeight" would seek an array
		/// member named "children", access the second member, and then
		/// look for a member named "blendWeight" in that object.
		void addBinding(const char* memberPath, int32_t variableIndex, Binding::BindingType bindingType = Binding::BindingType::BINDING_TYPE_VARIABLE, int8_t bitIndex = -1);

		HK_HEAP_REDEFINE_NEW();

		bool has_binding(const char* memberPath, int32_t variableIndex, Binding::BindingType bindingType = Binding::BindingType::BINDING_TYPE_VARIABLE, int8_t bitIndex = -1) const;

		// members
		hkArray<Binding> bindings;                      // 10
		int32_t          indexOfBindingToEnable{ -1 };  // 20
		bool             hasOutputBinding{ false };     // 24
		char             pad25[3];                      // 25
	};
	static_assert(sizeof(hkbVariableBindingSet) == 0x28);

	inline bool operator==(const hkbVariableBindingSet::Binding& lhs, const hkbVariableBindingSet::Binding& rhs);

	class hkbBindable;

	class hkbBindableCollector
	{
	public:
		// Called on each hkbBindable when you pass this collector into hkbBindable::collectBindables().
		virtual void collectBindable(hkbBindable* bindable) = 0;

		virtual ~hkbBindableCollector() = default;
	};

	class hkbBindable : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbBindable;
		inline static constexpr auto VTABLE = VTABLE_hkbBindable;

		struct Cache
		{
			// members
			hkbBindable* bindable;                // 00
			uint32_t     indexOfBindingToEnable;  // 08
			bool         hasOutputBinding;        // 0C
			char         pad0D[3];                // 0D
		};
		static_assert(sizeof(Cache) == 0x10);

		hkbBindable() { stl::emplace_vtable(this); }
		~hkbBindable() override = default;  // 00

		// add
		virtual void collectBindables(hkbBindableCollector& collector) { collector.collectBindable(this); }  // 03

		HK_HEAP_REDEFINE_NEW();

		void add_binding(const char* memberPath, int32_t variableIndex, hkbVariableBindingSet::Binding::BindingType bindingType = hkbVariableBindingSet::Binding::BindingType::BINDING_TYPE_VARIABLE, int8_t bitIndex = -1);
		void add_binding_nullcheck(const char* memberPath, int32_t variableIndex, hkbVariableBindingSet::Binding::BindingType bindingType = hkbVariableBindingSet::Binding::BindingType::BINDING_TYPE_VARIABLE, int8_t bitIndex = -1);
		bool has_binding(const char* memberPath, int32_t variableIndex, hkbVariableBindingSet::Binding::BindingType bindingType = hkbVariableBindingSet::Binding::BindingType::BINDING_TYPE_VARIABLE, int8_t bitIndex = -1) const;

		// members
		hkRefPtr<hkbVariableBindingSet> variableBindingSet;           // 10
		hkArray<Cache>                  cachedBindables;              // 18
		bool                            areBindablesCached{ false };  // 28
		char                            pad29[7];                     // 29
	};
	static_assert(sizeof(hkbBindable) == 0x30);
}
