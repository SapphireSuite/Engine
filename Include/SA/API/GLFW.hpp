// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_API_GLFW_GUARD
#define SAPPHIRE_API_GLFW_GUARD

#include <SA/Config.hpp>


// TODO: Add if compilation.
/// Sapphire Engine enable GLFW preprocessor.
#define SA_GLFW 1


#if SA_GLFW

#include <GLFW/glfw3.h>

namespace Sa::GLFW
{
	SA_ENGINE_API void Init();
	SA_ENGINE_API void UnInit();

	void WindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void CursorPositionCallback(GLFWwindow* _handle, double _posX, double _posY);
}

#endif

#endif // GUARD
