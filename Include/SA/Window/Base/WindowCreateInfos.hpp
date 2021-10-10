// Copyright 2020 Sapphire development team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_WINDOW_WINDOW_CREATE_INFOS_GUARD
#define SAPPHIRE_WINDOW_WINDOW_CREATE_INFOS_GUARD

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Window/Base/WindowMode.hpp>
#include <SA/Window/Base/CursorMode.hpp>

namespace Sa
{
	struct WindowCreateInfos
	{
		/// Window size.
		Vec2ui dimension = Vec2ui{ 1200u, 800u };

		/// Window position on screen.
		Vec2ui position;

		/// Window mode.
		WindowMode mode = WindowMode::Windowed;

		Flags<CursorMode> cursorFlags;

		/// Window name.
		std::string name = "Main Window";
	};
}

#endif // GUARD
