// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SA/Collections/Debug>

#include <SA/Support/API/GLFW.hpp>

#include <Window/GLFW/GLFWWindowInterface.hpp>
#include <Window/GLFW/GLFWWindow.hpp>

namespace Sa::GLFW
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

		mWindows.Clear();
	}


	AWindow* WindowInterface::CreateWindow(const WindowCreateInfos& _infos)
	{
		Window* window = mWindows.Emplace();

		window->Create(_infos);

		return window;
	}

	void WindowInterface::DestroyWindow(AWindow* _window)
	{
		SA_ASSERT(Nullptr, SA/Engine/Window/GLFW, _window);

		bool bRemoved = mWindows.Remove(_window);
		
		if(!bRemoved)
			SA_LOG(L"Window [" << _window << "] not created with this inferface.", Warning, SA/Engine/Window/GLFW);
	}


	bool WindowInterface::QueryRequiredExtensions(std::vector<const char*>& _extensions) const
	{
		// Query extensions.
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions = nullptr;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		_extensions.reserve(glfwExtensionCount);
		_extensions.insert(_extensions.end(), glfwExtensions, glfwExtensions + glfwExtensionCount);

		return true;
	}
}
