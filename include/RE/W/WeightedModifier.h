#pragma once

namespace RE
{
	template <typename T>
	class WeightedModifier
	{
	public:
		WeightedModifier(T a_data = T(), float a_weight = 1.0f) :
			weight(a_weight), data(std::move(a_data))
		{
		}

		~WeightedModifier() = default;
		WeightedModifier(const WeightedModifier&) = default;
		WeightedModifier& operator=(const WeightedModifier&) = default;

		// members
		float weight;  // 00
		T     data;    // 04
	};
}
