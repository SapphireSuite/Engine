// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_UTH_CONSOLE_THEME_GUARD
#define SAPPHIRE_UTH_CONSOLE_THEME_GUARD

#include <UTH/Step.hpp>
#include <SA/Core/Debug/ConsoleColor.hpp>

/**
*	\file ConsoleTheme.hpp
* 
*	\brief Console color theme used for test console output.
* 
*	\ingroup UTH
*	\{
*/

namespace Sa::UTH
{
	/// Console theme color class.
	class ConsoleTheme
	{
		uint8 mTheme[10]
		{
			(uint8)ConsoleColor::Reset,							// None.
			ConsoleColor::Bright_FG | ConsoleColor::Magenta_FG,	// Init.
			ConsoleColor::Bright_FG | ConsoleColor::Magenta_FG,	// Exit.
			ConsoleColor::Bright_FG | ConsoleColor::Yellow_FG,	// Title.
			(uint8)ConsoleColor::Green_FG,						// Success.
			(uint8)ConsoleColor::Red_FG,						// Failure.
			ConsoleColor::Bright_FG | ConsoleColor::Blue_FG,	// Group.
			ConsoleColor::Bright_FG | ConsoleColor::Yellow_FG,	// TestNum.
			(uint8)ConsoleColor::Yellow_FG						// ParamWarning.
		};

	public:

		/**
		*	\brief Set console output color from UTH Step.
		* 
		*	\param[in] _step	Current step.
		*/
		void SetConsoleColorFromStep(Step _step) const;
	};
}


/** \} */

#endif // GUARD
