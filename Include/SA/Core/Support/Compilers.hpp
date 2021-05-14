// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_COMPILERS_GUARD
#define SAPPHIRE_CORE_COMPILERS_GUARD

#include <SA/Core/Support/Version.hpp>

/**
*	\file Compilers.hpp
*
*	\brief \b Compiler support definition file.
*
*	Define compiler support preprocessors.
*
*	\ingroup Core
*	\{
*/


#if defined(_MSC_VER) || defined(DOXYGEN)

	/// Sapphire Engine MSVC compiler support preprocessor.
	#define SA_MSVC 1

	/// Sapphire Engine MSVC compiler version preprocessor.
	#define SA_MSVC_VERSION _MSC_FULL_VER

#else

	/// Sapphire Engine MSVC compiler support preprocessor.
	#define SA_MSVC 0

#endif

#if defined(__clang__) || defined(DOXYGEN)

	/// Sapphire Engine Clang compiler support preprocessor.
	#define SA_CLANG 1

	/// Sapphire Engine Clang compiler version preprocessor.
	#define SA_CLANG_VERSION SA_MAKE_VERSION(__clang_major__, __clang_minor__, __clang_patchlevel__)

#else

	/// Sapphire Engine Clang compiler support preprocessor.
	#define SA_CLANG 0

#endif

#if defined(__GNUC__) || defined(DOXYGEN)

	/// Sapphire Engine GNU compiler support preprocessor.
	#define SA_GNU 1

	/// Sapphire Engine GNU compiler version preprocessor.
	#define SA_GNU_VERSION SA_MAKE_VERSION(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)

#else

	/// Sapphire Engine GNU compiler support preprocessor.
	#define SA_GNU 0

#endif


/** \} */

#endif // GUARD
