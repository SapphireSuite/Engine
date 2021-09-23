// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_MEM_RESET_GUARD
#define SAPPHIRE_CORE_MEM_RESET_GUARD

#include <cstring> // std::mem*

#include <SA/Core/Debug.hpp>

/**
*	\file MemReset.hpp
*
*	\brief <b> Memory Reset </b> algorithm implementation.
*
*	\ingroup Core_Algorithms
*	\{
*/


namespace Sa
{
	/**
	*	\brief Reset a <b>block of memory</b>.
	*
	*	Reset the memory of size num * sizeof(T) from dest ptr.
	*	Internal use std::memset: std::mem* are already the most optimized.
	*
	*	\tparam T			Type of memory.
	*
	*	\param[out] _dest	Destination to reset.
	*	\param[in] _num		Number of T to reset.
	*/
	template <typename T>
	void MemReset(T* _dest, uint64 _num)
	{
		SA_ASSERT(Nullptr, Core, _dest);
		SA_ASSERT(NonZero, Core, _num, L"Number to copy is 0");

		std::memset(_dest, T(0), _num * sizeof(T));
	}
}


/** \} */

#endif // GUARD
