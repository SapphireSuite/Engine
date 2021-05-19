// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_INTRINSICS_GUARD
#define SAPPHIRE_CORE_INTRINSICS_GUARD

#include <SA/Core/Debug/Config.hpp>

#include <SA/Core/Support/ModuleAPI.hpp>
#include <SA/Core/Support/Compilers.hpp>
#include <SA/Core/Support/Architectures.hpp>

/**
*	\file Intrinsics.hpp
* 
*	\brief \b Intrinsics support file.
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

	/// Sapphire Engine intrinsics support preprocessor.
	#define SA_INTRISC 1

#endif


#if SA_INTRISC || defined(DOXYGEN)

	// SSE / SSE2.
	#if SA_x64

		/// SSE intrinsics support preprocessor.
		#define SA_INTRISC_SSE 1

		#include <immintrin.h>

	#else

		/// SSE intrinsics support preprocessor.
		#define SA_INTRISC_SSE 0

	#endif

	// AVX.
	#if __AVX__

		/// AVX intrinsics support preprocessor.
		#define SA_INTRISC_AVX 1

		#if SA_CLANG || SA_GNU

			#include <avxintrin.h>

		#endif

	#else

		/// AVX intrinsics support preprocessor.
		#define SA_INTRISC_AVX 0

	#endif


	// AVX2.
	#if __AVX2__

		/// AVX2 intrinsics support preprocessor.
		#define SA_INTRISC_AVX2 1

		#if SA_CLANG || SA_GNU

			#include <avx2intrin.h>

		#endif

	#else

		/// AVX2 intrinsics support preprocessor.
		#define SA_INTRISC_AVX2 0

	#endif


	// SVML.
	#if SA_MSVC && !SA_CLANG // Not supported on clang-cl.

		/// SVML intrinsics support preprocessor.
		#define SA_INTRISC_SVML 1

	#else

		/// SVML intrinsics support preprocessor.
		#define SA_INTRISC_SVML 0

	#endif

#endif


/** \} */

#endif // GUARD
