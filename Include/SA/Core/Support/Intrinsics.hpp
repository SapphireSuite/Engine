// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_INTRINSICS_GUARD
#define SAPPHIRE_CORE_INTRINSICS_GUARD

#include <SA/Core/Support/ModuleAPI.hpp>
#include <SA/Core/Support/Compilers.hpp>

/**
*	\file Intrinsics.hpp
* 
*	\brief Sapphire Engine intrinsics support file.
* 
*	Define intrinsics preprocessors and include support.
* 
*	\ingroup Core
*	\{
*/


#if SA_DEBUG

	/**
	*	\brief Sapphire Engine intrinsics support preprocessor.
	*	Never use intrinsics while in debug.
	*/
	#define SA_INTRISC 0

#else

	// TODO: Add intrinsics platform dependency.

	/// Sapphire Engine intrinsics support preprocessor.
	#define SA_INTRISC 1

#endif


#if SA_INTRISC || defined(DOXYGEN)

	#include <immintrin.h>

	#if SA_CLANG || SA_GNU

		#include <avxintrin.h>
		#include <avx2intrin.h>

		/// Sapphire Engine intrinsics SVML support preprocessor.
		#define SA_INTRISC_SVML 0

	#elif SA_MSVC

		/// Sapphire Engine intrinsics SVML support preprocessor.
		#define SA_INTRISC_SVML 1

	#endif

#endif


/** \} */

#endif // GUARD
