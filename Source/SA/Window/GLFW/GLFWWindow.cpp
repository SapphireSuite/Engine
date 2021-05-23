// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Window/GLFW/GLFWWindow.hpp>

#include <Window/GLFW/GLFW.hpp>

#if SA_GLFW

#include <glfw/glfw3.h>

namespace Sa::GLFW
{
	void Window::Create(uint32 _width, uint32 _height, const std::string& _name)
	{
		GLFW::Init();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		mHandle = glfwCreateWindow(_width, _height, _name.c_str(), nullptr, nullptr);

		SA_ASSERT(Default, Window/GLFW, mHandle, L"GLFW create window failed!");
	}
	
	void Window::Destroy()
	{
		SA_ASSERT(Nullptr, Window/GLFW, mHandle, L"Try to destroy a non-created window, call Create() first.");

		glfwDestroyWindow(mHandle);
		mHandle = nullptr;

		GLFW::UnInit();
	}


	void Window::Update()
	{
		GLFW::PollEvents();
	}

	bool Window::ShouldClose() const
	{
		return glfwWindowShouldClose(mHandle);
	}
}

#endif