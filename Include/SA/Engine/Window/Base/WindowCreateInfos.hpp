// Copyright (c) 2022 Sapphire development team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_WINDOW_CREATE_INFOS_GUARD
#define SAPPHIRE_ENGINE_WINDOW_CREATE_INFOS_GUARD

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Engine/Window/Base/WindowMode.hpp>
#include <SA/Engine/Window/Base/CursorMode.hpp>

namespace SA
{
	struct WindowCreateInfos
	{
		/// Window size.
		Vec2ui dimension = Vec2ui{ 1200u, 800u };

		/// Window position on screen.
		Vec2ui position = { 300, 200 };

		/// Window mode.
		WindowMode windowMode = WindowMode::Windowed;

		/// Cursor mode flags.
		Flags<CursorMode> cursorMode = CursorMode::None;

		/// Minimized state.
		bool bMinimized = false;

		/// Maximized state.
		bool bMaximized = false;

		/// Window name.
		std::string name = "Main Window";
	};
}

#endif // GUARD
