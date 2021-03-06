// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SA/Collections/Debug>

#include <SA/Support/API/GLFW.hpp>

#include <Window/GLFW/GLFWWindowInterface.hpp>
#include <Window/GLFW/GLFWWindow.hpp>

namespace SA::GLFW
{
	void ErrorCallback(int32_t error, const char* description)
	{
		SA_LOG(L"GLFW Error [" << error << L"]:" << description, Error, SA/Engine/Window/GLFW);
	}

	void WindowInterface::Create()
	{
		AWindowInterface::Create();

		glfwSetErrorCallback(ErrorCallback);

		SA_ASSERT_EXEC(Default, SA/Engine/Window/GLFW, glfwInit(), L"GLFW init failed!");

		SA_LOG(L"Window Interface created.", Infos, SA/Engine/Window/GLFW);
	}

	void WindowInterface::Destroy()
	{
		AWindowInterface::Destroy();

		glfwTerminate();

		SA_LOG(L"Window Interface destroyed.", Infos, SA/Engine/Window/GLFW);
	}

	void WindowInterface::Clear()
	{
		AWindowInterface::Clear();

		mWindows.Clear(DestroyFunctor<Window>());

		SA_LOG(L"Window Interface cleared.", Infos, SA/Engine/Window/GLFW);
	}


	AWindow* WindowInterface::CreateWindow(const WindowCreateInfos& _infos)
	{
		CheckCreated();

		Window* window = mWindows.Emplace();

		window->Create(_infos);

		return window;
	}

	void WindowInterface::DestroyWindow(AWindow* _window)
	{
		CheckCreated();

		SA_ASSERT(Nullptr, SA/Engine/Window/GLFW, _window);

		bool bRemoved = mWindows.Erase(_window, DestroyFunctor<Window>());
		
		if(!bRemoved)
			SA_LOG(L"Window [" << _window << "] not created with this inferface.", Warning, SA/Engine/Window/GLFW);
	}


	bool WindowInterface::QueryRequiredExtensions(std::vector<const char*>& _extensions) const
	{
		CheckCreated();

		// Query extensions.
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions = nullptr;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		_extensions.reserve(glfwExtensionCount);
		_extensions.insert(_extensions.end(), glfwExtensions, glfwExtensions + glfwExtensionCount);

		return true;
	}
}
