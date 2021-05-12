// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_CONSOLE_COLOR_GUARD
#define SAPPHIRE_CORE_CONSOLE_COLOR_GUARD

#include <SA/Config.hpp>

#include <SA/Core/Debug/Config.hpp>

#include <SA/Core/Types/Variadics/Flags.hpp>

namespace Sa
{
#if SA_LOGGING

	/**
	*
	*	Bright BG bit		BG Color bits		Bright FG bit		FG Color bits
	*		0					000					0					000
	*/
	enum class ConsoleColor : uint8
	{
		// 4 bits for foreground attributes.

		// 3 bits for foreground color.
		None_FG = 0,
		Red_FG = 1,
		Green_FG = 2,
		Blue_FG = 3,
		Cyan_FG = 4,
		Magenta_FG = 5,
		Yellow_FG = 6,
		Black_FG = 7,

		// 1 bit for bright attribute.
		Bright_FG = 8,


		// 4 bits for background attributes.

		// 3 bits for background color.
		None_BG = 0 << 4,
		Red_BG = 1 << 4,
		Green_BG = 2 << 4,
		Blue_BG = 3 << 4,
		Cyan_BG = 4 << 4,
		Magenta_BG = 5 << 4,
		Yellow_BG = 6 << 4,
		White_BG = 7 << 4,

		// 1 bit for Bright attribute.
		Bright_BG = 8 << 4,

		// Reset console color value.
		Reset = None_FG | None_BG,
	};

	using CslColor = ConsoleColor;

	SA_DEFINE_ENUM_FLAGS(ConsoleColor);

	/**
	*	\brief \e Crossplatform implementation of set color in console.
	* 
	*	\param[in] _cslColor	Console color.
	*/
	SA_ENGINE_API void SetConsoleColor(ConsoleColor _cslColor);

	/**
	*	\brief \e Crossplatform implementation of set color in console.
	* 
	*	\param[in] _cslColorMask	Console color mask.
	*/
	SA_ENGINE_API void SetConsoleColor(uint8 _cslColorMask);

#endif
}

#endif // GUARD
