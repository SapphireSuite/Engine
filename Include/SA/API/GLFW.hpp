// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_API_GLFW_GUARD
#define SAPPHIRE_API_GLFW_GUARD


// TODO: Add if compilation.
/// Sapphire Engine enable GLFW preprocessor.
#define SA_GLFW 1


#if SA_GLFW

struct GLFWwindow;

namespace Sa::GLFW
{
	void Init();
	void UnInit();

	void WindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
}

#endif

#endif // GUARD
