// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_DEBUG_CONFIG_GUARD
#define SAPPHIRE_CORE_DEBUG_CONFIG_GUARD

/**
*	\file SA/Core/Debug/Config.hpp
*
*	\brief <b>Core Debug</b> config file.
* 
*	\ingroup Core_Debug
*	\{
*/


#if !defined(NDEBUG) || defined(_DEBUG)

	/// Sapphire Engine Debug preprocessor.
	#define SA_DEBUG 1

#else

	/// Sapphire Engine Debug preprocessor.
	#define SA_DEBUG 0

#endif

#if !defined(__SA_LOG_RELEASE) || defined(DOXYGEN)

	/// Enable log in release.
	#define __SA_LOG_RELEASE 0

#endif


/// Sapphire Engine enable Logging preprocessor.
#define SA_LOGGING SA_DEBUG || __SA_LOG_RELEASE


/** \} */

#endif // GUARD
