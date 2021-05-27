// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_WINDOW_GLFW_GUARD
#define SAPPHIRE_WINDOW_GLFW_GUARD

// TODO: REMOVE LATER.
#include <SA/Config.hpp>

#include <SA/Window/Config.hpp>

#if SA_GLFW

struct GLFWwindow;

namespace Sa::GLFW
{
	void Init();
	void UnInit();

	// TODO: Remove SA_ENGINE_API.
	SA_ENGINE_API void PollEvents();

	void WindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
}

#endif

#endif // GUARD
