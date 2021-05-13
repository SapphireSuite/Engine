// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_MEM_FILL_GUARD
#define SAPPHIRE_CORE_MEM_FILL_GUARD

#include <algorithm>

#include <SA/Collections/Debug>

/**
*	\file MemFill.hpp
*
*	\brief \b Definition of Sapphire Engine <b> Memory Fill </b> algorithm.
*
*	\ingroup Core_Algorithms
*	\{
*/


namespace Sa
{
	/**
	*	\brief Fill a <b>block of memory</b> with val.
	*
	*	Fill the memory of size: num * sizeof(T) from dest ptr.
	*	Internal use std::fill: std::mem* are already the most optimized.
	*
	*	\tparam T			Type of memory.
	*
	*	\param[out] _dest	Destination to fill.
	*	\param[in] _val		Value to fill with.
	*	\param[in] _num		Number of T to fill.
	*/
	template <typename T>
	void MemFill(T* _dest, const T& _val, uint64 _num)
	{
		SA_ASSERT(Nullptr, Core, _dest);
		SA_ASSERT(NonZero, Core, _num, L"Number to copy is 0");

		std::fill(_dest, _dest + _num, _val);
	}
}


/** \} */

#endif // GUARD
