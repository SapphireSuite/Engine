// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_BIT_SCAN_FORWARD_GUARD
#define SAPPHIRE_CORE_BIT_SCAN_FORWARD_GUARD

#include <SA/Core/Types/Int.hpp>

#include <SA/Core/Support/Platforms.hpp>

#if SA_WIN

	#include <intrin.h>

#else
#endif

/**
*	\file BitScanForward.hpp
* 
*	\brief BitScanForward \e cross-platform implementation.
* 
*	\ingroup Core
*	\{
*/


namespace Sa
{
	/**
	*	\brief \e Cross-platform \b BitScanForward implementation.
	* 
	*	\param[in] _mask	Mask to scan.
	* 
	*	\return Index of first set bit or -1 if no set bit found.
	*/
	inline uint32 BitScanForward(uint32 _mask)
	{
		if (!_mask)
			return ~uint32();

		unsigned long index = 0u;

#if SA_WIN

		_BitScanForward(&index, _mask);
#else

		// __builtin_ffs returns 1 + index if non zero.
		index = __builtin_ffs(_mask) - 1;
#endif

		return static_cast<uint32>(index);
	}
}


/** \} */

#endif // GUARD