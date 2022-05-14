// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_WINDOW_MODE_GUARD
#define SAPPHIRE_ENGINE_WINDOW_MODE_GUARD

#include <cstdint>

/**
*	\file WindowMode.hpp
*
*	\brief Window mode enum definition.
*
*	\ingroup Window
*	\{
*/


namespace SA
{
	/// Window mode enum.
	enum class WindowMode : uint8_t
	{
		/// Windowed.
		Windowed = 1,

		/// FullScreen.
		FullScreen,

		/// Borderless fullscreen.
		Borderless,
	};
}


/** \} */

#endif // GUARD
