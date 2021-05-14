// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_PLATFORMS_GUARD
#define SAPPHIRE_CORE_PLATFORMS_GUARD

/**
*	\file Platforms.hpp
*
*	\brief \b Platform support definition file.
*
*	Define platform support preprocessors.
*
*	\ingroup Core
*	\{
*/


#if defined(_WIN32) || defined(_WIN64) || defined(DOXYGEN)

	/// Sapphire Engine Windows platform support preprocessor.
	#define SA_WIN 1

#else

	/// Sapphire Engine Windows platform support preprocessor.
	#define SA_WIN 0

#endif

#if defined(__ANDROID__)

	/// Sapphire Engine Android platform support preprocessor.
	#define SA_ANDROID 1

#else

	/// Sapphire Engine Android platform support preprocessor.
	#define SA_ANDROID 0

#endif

#if defined(__linux__)

	/// Sapphire Engine Unix platform support preprocessor.
	#define SA_UNIX 1

#else

	/// Sapphire Engine Unix platform support preprocessor.
	#define SA_UNIX 0

#endif

#if defined(__APPLE__)

	/// Sapphire Engine MacOS platform support preprocessor.
	#define SA_OSX 1

#else

	/// Sapphire Engine MacOS platform support preprocessor.
	#define SA_OSX 0

#endif


/** \} */


#endif // GUARD
