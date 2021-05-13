// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_MEM_COPY_GUARD
#define SAPPHIRE_CORE_MEM_COPY_GUARD

#include <cstring> // std::mem*

#include <SA/Collections/Debug>

/**
*	\file MemCopy.hpp
*
*	\brief \b Definition of Sapphire Engine <b> Memory Copy </b> algorithm.
*
*	\ingroup Core_Algorithms
*	\{
*/


namespace Sa
{
	/**
	*	\brief Copy a <b>block of memory</b> from src to dest of num object.
	*
	*	Copy the memory of size: num * sizeof(T) from src to dest ptr.
	*	Internal use std::memcpy: std::mem* are already the most optimized.
	*
	*	\tparam T			Type of memory.
	*
	*	\param[in] _src		Source to copy from.
	*	\param[out] _dest	Destination to copy to.
	*	\param[in] _num		Number of T to copy.
	*/
	template <typename T>
	void MemCopy(const T* _src, T* _dest, uint64 _num)
	{
		SA_ASSERT(Nullptr, Core, _src);
		SA_ASSERT(Nullptr, Core, _dest);
		SA_ASSERT(NonZero, Core, _num, L"Number to copy is 0");

		std::memcpy(_dest, _src, _num * sizeof(T));
	}
}


/** \} */

#endif // GUARD
