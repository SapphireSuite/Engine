// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/GLFW/GLFWInputSystem.hpp>

#include <Input/GLFW/GLFWInputWindowContext.hpp>

#include <Window/GLFW/GLFWWindow.hpp>

#if SA_GLFW

namespace Sa::GLFW
{
	IInputWindowContext* InputSystem::InstantiateWindowContext(IWindow* _win)
	{
		return new GLFW::InputWindowContext{ _win->AsPtr<GLFW::Window>() };
	}


	void InputSystem::Update()
	{
		glfwPollEvents();
	}
}

#endif
