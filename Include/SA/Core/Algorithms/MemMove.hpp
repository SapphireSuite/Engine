// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_MEM_MOVE_GUARD
#define SAPPHIRE_CORE_MEM_MOVE_GUARD

#include <cstring> // std::mem*

#include <SA/Collections/Debug>

/**
*	\file MemMove.hpp
*
*	\brief <b>Memory Move</b> algorithm implementation.
*
*	\ingroup Core_Algorithms
*	\{
*/


namespace Sa
{
	/**
	*	\brief Move a <b>block of memory</b> from src to dest of num object.
	*
	*	Move the memory of size: num * sizeof(T) from src to dest ptr.
	*	Internal use std::memmove: std::mem* are already the most optimized.
	*
	*	\tparam T			Type of memory.
	*
	*	\param[in] _src		Source to move from.
	*	\param[out] _dest	Destination to move to.
	*	\param[in] _num		Number of T to move.
	*/
	template <typename T>
	void MemMove(const T* _src, T* _dest, uint64 _num)
	{
		SA_ASSERT(Nullptr, Core, _src);
		SA_ASSERT(Nullptr, Core, _dest);
		SA_ASSERT(NonZero, Core, _num, L"Number to copy is 0");

		std::memmove(_dest, _src, _num * sizeof(T));
	}
}


/** \} */

#endif // GUARD
