// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_ARCHITECTURES_GUARD
#define SAPPHIRE_CORE_ARCHITECTURES_GUARD

/**
*	\file Architectures.hpp
*
*	\brief Sapphire Engine architecture support definition file.
*
*	Define architecture support preprocessors.
*
*	\ingroup Core
*	\{
*/


#if defined(__x86_64__) || defined(_M_AMD64)

	/// Sapphire Engine x32 architecture support preprocessor.
	#define SA_x32 0

	/// Sapphire Engine x64 architecture support preprocessor.
	#define SA_x64 1

#else

	/// Sapphire Engine x32 architecture support preprocessor.
	#define SA_x32 1

	/// Sapphire Engine x64 architecture support preprocessor.
	#define SA_x64 0

#endif


#if defined(__arm__) || defined(_M_ARM)

	/// Sapphire Engine arm architecture support preprocessor.
	#define SA_ARM 1

#else

	/// Sapphire Engine arm architecture support preprocessor.
	#define SA_ARM 0

#endif


/** \} */


#endif // GUARD
