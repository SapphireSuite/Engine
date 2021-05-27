// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_UTH_RANDOM_GUARD
#define SAPPHIRE_UTH_RANDOM_GUARD

#include <cstdlib>

// TODO: Remove later, use Engine Random impl.

/**
*	\file Random.hpp
* 
*	\brief Fast Random implementation.
* 
*	\ingroup UTH
*	\{
*/


namespace Sa::UTH
{
	/**
	*	\brief Rand between [min, max[ (max excluded).
	*
	*	\tparam T			Type of the rand.
	*	\param[in] _min		Min bound for rand (included).
	*	\param[in] _max		Max bound for rand (excluded).
	*
	*	\return Random T between [min, max[ (max excluded).
	*/
	template <typename T>
	T Rand(T _min = T(0), T _max = T(1))
	{
		return _min + static_cast<T>(rand()) / static_cast<T>(RAND_MAX / (_max - _min));
	}

	/**
	*	\brief Rand specialization for bool.
	*
	*	\param[in] _min		Min bound (false) (included).
	*	\param[in] _max		Max bound (true) (included).
	*
	*	\return Random bool.
	*/
	template<>
	inline bool Rand(bool _min, bool _max) { (void)_min; (void)_max; return Rand<int>(0, 2) == 1; }
}


/** \} */

#endif // GUARD
