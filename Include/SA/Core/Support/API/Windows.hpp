// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_WINDOWS_API_GUARD
#define SAPPHIRE_CORE_WINDOWS_API_GUARD

#include <SA/Core/Support/Pragma.hpp>
#include <SA/Core/Support/Platforms.hpp>

/**
*	\file Windows.hpp
*
*	\brief \b Windows.h support file.
*
*	\ingroup Core
*	\{
*/


#if SA_WIN

	/**
	*	Remove macro producing 'define' expansion warning.
	*	See: https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/c5105
	*/
	SA_PRAGMA_SDWARN_MSVC(5105)

	#include <Windows.h>

	SA_PRAGMA_EDWARN()

#endif


/** \} */

#endif // GUARD
