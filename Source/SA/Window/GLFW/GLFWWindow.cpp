// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Window/GLFW/GLFWWindow.hpp>

#include <Input/GLFW/GLFWInputWindowContext.hpp>

#if SA_GLFW

namespace Sa::GLFW
{
	void Window::SetWindowMode(WindowMode _mode)
	{
		if (_mode == GetWindowMode())
			return;

		GLFWmonitor* const currMonitor = GetCurrentMonitor();
		const GLFWvidmode* const mode = glfwGetVideoMode(currMonitor);
		const Vec2i newSize = Vec2i{ mode->width, mode->height };


		// Previous mode was windowed: save values.
		if (GetWindowMode() == WindowMode::Windowed)
		{
			mSavedSize = GetSize();
			glfwGetWindowPos(mHandle, &mSavedPosition.x, &mSavedPosition.y);
		}


		switch (_mode)
		{
			case WindowMode::Windowed:
			{
				glfwSetWindowMonitor(mHandle, nullptr, mSavedPosition.x, mSavedPosition.y, mSavedSize.x, mSavedSize.y, NULL);
				break;
			}
			case WindowMode::FullScreen:
			{
				glfwSetWindowMonitor(mHandle, currMonitor, 0, 0, newSize.x, newSize.y, mode->refreshRate);
				break;
			}
			case WindowMode::Borderless:
			{
				// Full screen before.
				if (GetWindowMode() == WindowMode::FullScreen)
				{
					// Ensure correct desktop resolution.
					// Source: https://www.glfw.org/docs/3.3/window_guide.html#window_windowed_full_screen

					SetWindowMode(WindowMode::Windowed);
					SetWindowMode(WindowMode::Borderless);
				}
				else
					glfwSetWindowMonitor(mHandle, nullptr, 0, 0, newSize.x, newSize.y, mode->refreshRate);

				break;
			}
			default:
			{
				SA_LOG(L"WindowMode [" << _mode << "] not supported yet!", Warning, SA/Window/GLFW);
				break;
			}
		}

		AWindow::SetWindowMode(_mode);
	}


	void Window::Create(const CreateInfos& _infos)
	{
		AWindow::Create(_infos);

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		mHandle = glfwCreateWindow(_infos.dimension.x, _infos.dimension.y, _infos.name.c_str(), nullptr, nullptr);

		SA_ASSERT(Default, Window/GLFW, mHandle, L"GLFW create window failed!");

		glfwSetWindowUserPointer(mHandle, this);
		glfwSetWindowSizeCallback(mHandle, ResizeCallback);
		glfwSetWindowIconifyCallback(mHandle, MinimizedCallback);
		glfwSetWindowMaximizeCallback(mHandle, MaximizedCallback);

		SetWindowMode(_infos.mode);

		SA_LOG(L"Window created", Infos, SA/Window/GLFW);
	}
	
	void Window::Destroy()
	{
		SA_ASSERT(Nullptr, Window/GLFW, mHandle, L"Try to destroy a non-created window, call Create() first.");

		glfwDestroyWindow(mHandle);
		mHandle = nullptr;

		SA_LOG(L"Window destroyed", Infos, SA/Window/GLFW);
	}

	AInputWindowContext* Window::GetInputWindowContext() const
	{
		return inputWinContext;
	}


	void Window::Close()
	{
		glfwSetWindowShouldClose(mHandle, GLFW_TRUE);
	}

	bool Window::ShouldClose() const
	{
		return glfwWindowShouldClose(mHandle);
	}


	void Window::MinimizedCallback(GLFWwindow* _handle, int32 _minimized)
	{
		GLFW::Window* const win = static_cast<GLFW::Window*>(glfwGetWindowUserPointer(_handle));
		SA_ASSERT(Nullptr, SA/Window/GLFW, win);

		win->SetMinimized(_minimized);
	}

	void Window::MaximizedCallback(GLFWwindow* _handle, int32 _maximized)
	{
		GLFW::Window* const win = static_cast<GLFW::Window*>(glfwGetWindowUserPointer(_handle));
		SA_ASSERT(Nullptr, SA/Window/GLFW, win);

		win->SetMaximized(_maximized);
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


	GLFWmonitor* Window::GetCurrentMonitor() const
	{
		// Source: https://stackoverflow.com/questions/21421074/how-to-create-a-full-screen-window-on-the-current-monitor-with-glfw

		Vec2i winPos;
		glfwGetWindowPos(mHandle, &winPos.x, &winPos.y);

		const Vec2i winSize = GetSize();

		int32 num = 0;
		int32 bestOverlap = 0;
		GLFWmonitor* const * const monitors = glfwGetMonitors(&num);
		GLFWmonitor* bestMonitor = glfwGetPrimaryMonitor();

		for (int32 i = 0u; i < num; ++i)
		{
			Vec2i monPos;
			glfwGetMonitorPos(monitors[i], &monPos.x, &monPos.y);

			const GLFWvidmode* const mode = glfwGetVideoMode(monitors[i]);

			const int32 overlap = std::max(0, std::min(winPos.x + winSize.x, monPos.x + mode->width) - std::max(winPos.x, monPos.x));

			if (overlap > bestOverlap)
			{
				bestOverlap = overlap;
				bestMonitor = monitors[i];
			}
		}

		return bestMonitor;
	}


	GLFWwindow* Window::GetHandle() const
	{
		return mHandle;
	}
}

#endif