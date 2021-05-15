// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Core/Misc/Random.hpp>

namespace Sa
{
//{ RandomEngine

	std::random_device RandomEngine::defaultEngine;

	RandomEngine::RandomEngine(uint32 _seed) noexcept : handle{ _seed }
	{
	}

//}

//{ Random

//{ Random bool

	bool Random<bool>::Value(RandomEngine* _en) noexcept
	{
		static std::uniform_int_distribution<int16> dist(0, 1);

		return _en ? dist(_en->handle) : dist(RandomEngine::defaultEngine);
	}

//}

//{ Random int

	template <>
	int32 Random<int32>::Value(int32 _min, int32 _max, RandomEngine* _en) noexcept
	{
		std::uniform_int_distribution<int32> dist(_min, _max - 1); // Exclude max.

		return _en ? dist(_en->handle) : dist(RandomEngine::defaultEngine);
	}

	template <>
	uint32 Random<uint32>::Value(uint32 _min, uint32 _max, RandomEngine* _en) noexcept
	{
		std::uniform_int_distribution<uint32> dist(_min, _max - 1u); // Exclude max.

		return _en ? dist(_en->handle) : dist(RandomEngine::defaultEngine);
	}

//}

//{ Random float

	float Random<float>::Value(float _min, float _max, RandomEngine* _en) noexcept
	{
		std::uniform_real_distribution<float> dist(_min, _max - std::numeric_limits<float>::epsilon()); // Exclude max.

		return _en ? dist(_en->handle) : dist(RandomEngine::defaultEngine);
	}

	float Random<float>::Value01(RandomEngine* _en) noexcept
	{
		return Value(0.0f, 1.0f, _en);
	}


	double Random<double>::Value(double _min, double _max, RandomEngine* _en) noexcept
	{
		std::uniform_real_distribution<double> dist(_min, _max - std::numeric_limits<double>::epsilon()); // Exclude max.

		return _en ? dist(_en->handle) : dist(RandomEngine::defaultEngine);
	}

	double Random<double>::Value01(RandomEngine* _en) noexcept
	{
		return Value(0.0, 1.0, _en);
	}

//}

//}
}
