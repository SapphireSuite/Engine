// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/GLFW/GLFWInputSystem.hpp>

#if SA_GLFW

#include <GLFW/glfw3.h>

namespace Sa
{
	void GLFWInputSystem::Update()
	{
		glfwPollEvents();
	}
}

#endif
