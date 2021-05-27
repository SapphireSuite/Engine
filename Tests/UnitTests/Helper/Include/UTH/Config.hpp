// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_UTH_CONFIG_GUARD
#define SAPPHIRE_UTH_CONFIG_GUARD

#include <SA/Core/Support/ModuleAPI.hpp>

/**
*	\file UTH/Config.hpp
*
*	\brief Sapphire Engine UnitTestHelper module config file.
* 
*	\ingroup UTH
*	\{
*/


#if defined(SA_UnitTestHelper_EXPORTS)

	/// Sapphire Engine API import/export preprocessor.
	#define SA_UTH_API SA_MODUE_EXPORT

#else

	/// Sapphire Engine API import/export preprocessor.
	#define SA_UTH_API SA_MODUE_IMPORT

#endif


#ifndef SA_UTH_EXIT_ON_FAILURE

	/**
	*	\brief Wether to exit program on failure or continue next tests.
	*	Can be defined within cmake options or before including the header.
	*/
	#define SA_UTH_EXIT_ON_FAILURE 0

#endif

#ifndef SA_UTH_EXIT_PAUSE

	/**
	*	\brief Whether to pause program on exit.
	*	Always disabled in continuous integration (define SA_CI).
	*/
	#define SA_UTH_EXIT_PAUSE 0

#endif

namespace Sa
{
	/// Unit Test Helper module main namespace.
	namespace UTH
	{
		/// UTH Internal classes implementations.
		namespace Intl
		{
		}
	}
}


/**
*	\defgroup UTH UnitTestHelper
*	Sapphire Engine Unit Test Helper module.
*/


/** \} */

#endif // GUARD
