// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_WINDOW_WINDOW_MODE_GUARD
#define SAPPHIRE_WINDOW_WINDOW_MODE_GUARD

#include <SA/Core/Types/Int.hpp>

/**
*	\file WindowMode.hpp
* 
*	\brief Window mode enum definition.
* 
*	\ingroup Window
*	\{
*/

namespace Sa
{
	/// Window mode enum.
	enum class WindowMode : uint8
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
