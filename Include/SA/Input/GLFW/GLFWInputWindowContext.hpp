// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_GLFW_INPUT_WINDOW_CONTEXT_GUARD
#define SAPPHIRE_INPUT_GLFW_INPUT_WINDOW_CONTEXT_GUARD

#include <SA/Core/Support/API/GLFW.hpp>

#include <SA/Input/Base/AInputWindowContext.hpp>

#include <SA/Maths/Space/Vector2.hpp>

#if SA_GLFW

namespace Sa::GLFW
{
	class Window;

	class InputWindowContext : public AInputWindowContext
	{
		Vec2f mSavedMousePos;

	public:
		InputWindowContext(Window* _win);

		void WindowKeyCallback(const InputKey& _inRawKey);
		void CursorPositionCallback(const Vec2ui& _windowSize, const Vec2f& _mousePos);
	};
}

#endif

#endif // GUARD
