// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_UTH_STEP_CONSOLE_COLOR_GUARD
#define SAPPHIRE_UTH_STEP_CONSOLE_COLOR_GUARD

#include <SA/Core/Types/Int.hpp>

/**
*	\file Step.hpp
* 
*	\brief UTH execution step color enum.
* 
*	\ingroup UTH
*	\{
*/


namespace Sa::UTH
{
	/// enum for console colors.
	enum class Step : uint8
	{
		/// Default color.
		None,

		/// UTH Color for init.
		Init,

		/// UTH Color for exit.
		Exit,

		/// Color used for test's titles.
		Title,

		/// Color used on test success.
		Success,

		/// Color used on test failure.
		Failure,

		/// Color used for groups.
		Group,

		/// Color used for test number.
		TestNum,

		/// Color used for param warning.
		ParamWarning,
	};
}


/** \} */

#endif // GUARD
