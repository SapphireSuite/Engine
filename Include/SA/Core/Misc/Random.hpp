// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_RANDOM_GUARD
#define SAPPHIRE_CORE_RANDOM_GUARD

#include <limits>
#include <random>

#include <SA/Collections/Debug>

/**
*	\file Random.hpp
*
*	\brief <b>Random generator</b> classes definition.
*
*	\ingroup Core_Misc
*	\{
*/


namespace Sa
{
//{ RandomEngine

	/**
	*	\brief Handle \e std::default_random_engine class
	*
	*	Use std:: implementation and Sapphire's norm.
	*	See more documentation: http://www.cplusplus.com/reference/random/default_random_engine/
	*/
	class RandomEngine
	{
	public:
		/// Handled std::default_random_engine.
		std::default_random_engine handle;

		/// Default unseeded hardware-dependant random implementation.
		SA_ENGINE_API static std::random_device defaultEngine;

		/**
		*	\brief \e Value constructor.
		*
		*	\param[in] _seed	Seed to initialize the random engine.
		*/
		SA_ENGINE_API RandomEngine(uint32 _seed = 0u) noexcept;
	};

	/// Shortcut alias.
	using RandEn = RandomEngine;

//}

//{ Random

	/**
	*	\brief \e Generate a random value of type T in range [min;max[.
	*
	*	random values range: min <= rand < max
	*
	*	\tparam T	Type of the random.
	*/
	template <typename T>
	class Random
	{
	public:
		/**
		*	\brief \e Generate a \b random T-value in range [min;max[.
		*
		*	random values range: min <= rand < max
		*
		*	\param[in] _min		Included min.
		*	\param[in] _max		Excluded max.
		*	\param[in] _en		Seeded Engine (or null for unseeded).
		*
		*	\return Generated random in range [min;max[.
		*/
		static T Value(T _min, T _max, RandomEngine* _en = nullptr) noexcept;
	};
	
	/// \cond Internal
	
//{ Random bool

	/**
	*	\brief Random \e specialization for \c bool.
	*
	*	\implements Random
	*/
	template <>
	class Random<bool>
	{
	public:
		/**
		*	\brief \e Generate a \b random bool value.
		*
		*	\param[in] _en	Seeded Engine (or null for unseeded).
		*
		*	\return Generated random bool (true or false).
		*/
		SA_ENGINE_API static bool Value(RandomEngine* _en = nullptr) noexcept;
	};

//}

//{ Random int

	template <>
	SA_ENGINE_API int32 Random<int32>::Value(int32 _min, int32 _max, RandomEngine* _en) noexcept;

	template <>
	SA_ENGINE_API uint32 Random<uint32>::Value(uint32 _min, uint32 _max, RandomEngine* _en) noexcept;

//}

//{ Random float

	template <>
	class Random<float>
	{
	public:
		SA_ENGINE_API static float Value(
			float _min = std::numeric_limits<float>::min(),
			float _max = std::numeric_limits<float>::max(),
			RandomEngine* _en = nullptr) noexcept;

		SA_ENGINE_API static float Value01(RandomEngine* _en = nullptr) noexcept;
	};

	template <>
	class Random<double>
	{
	public:
		SA_ENGINE_API static double Value(
			double _min = std::numeric_limits<double>::min(),
			double _max = std::numeric_limits<double>::max(),
			RandomEngine* _en = nullptr) noexcept;

		SA_ENGINE_API static double Value01(RandomEngine* _en = nullptr) noexcept;
	};

//}
	
	/// \endcond Internal

//}
}


/** \} */

#endif // GUARD
