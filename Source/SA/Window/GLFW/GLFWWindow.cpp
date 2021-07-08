// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Window/GLFW/GLFWWindow.hpp>

#if SA_GLFW

namespace Sa::GLFW
{
	void Window::Create(uint32 _width, uint32 _height, const std::string& _name)
	{
		IWindow::Create(_width, _height, _name);

		GLFW::Init();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		mHandle = glfwCreateWindow(_width, _height, _name.c_str(), nullptr, nullptr);

		SA_ASSERT(Default, Window/GLFW, mHandle, L"GLFW create window failed!");

		glfwSetWindowUserPointer(mHandle, this);
		glfwSetWindowIconifyCallback(mHandle, MinimizedCallback);
		glfwSetWindowSizeCallback(mHandle, ResizeCallback);

		mInput.Create(mHandle);
	}
	
	void Window::Destroy()
	{
		SA_ASSERT(Nullptr, Window/GLFW, mHandle, L"Try to destroy a non-created window, call Create() first.");

		mInput.Destroy();

		glfwDestroyWindow(mHandle);
		mHandle = nullptr;

		GLFW::UnInit();
	}


	IInputSystem& Window::GetInputSystem()
	{
		return mInput;
	}


	void Window::Close()
	{
		glfwSetWindowShouldClose(mHandle, GLFW_TRUE);
	}

	bool Window::ShouldClose() const
	{
		return glfwWindowShouldClose(mHandle);
	}


	void Window::ResizeCallback(GLFWwindow* _handle, int32 _width, int32 _height)
	{
		GLFW::Window* const win = static_cast<GLFW::Window*>(glfwGetWindowUserPointer(_handle));
		SA_ASSERT(Nullptr, SA/Window/GLFW, win);

		Vec2ui newSize = Vec2i{ _width, _height };

		// Window minimized (in/out).
		if (win->IsMinimized() || newSize == win->GetSize())
			return;

		win->SetSize(newSize);
	}

	void Window::MinimizedCallback(GLFWwindow* _handle, int32 _iconified)
	{
		GLFW::Window* const win = static_cast<GLFW::Window*>(glfwGetWindowUserPointer(_handle));
		SA_ASSERT(Nullptr, SA/Window/GLFW, win);

		win->SetMinimized(_iconified);
	}
}

#endif