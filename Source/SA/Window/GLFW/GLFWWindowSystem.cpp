// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Window/GLFW/GLFWWindowSystem.hpp>

#include <Core/Debug.hpp>

#if SA_GLFW

namespace Sa::GLFW
{
	void ErrorCallback(int32 error, const char* description)
	{
		SA_LOG(L"GLFW Error [" << error << L"]:" << description, Error, SA/Window/GLFW);
	}

	void WindowSystem::Create()
	{
		glfwSetErrorCallback(ErrorCallback);

		SA_ASSERT_EXEC(Default, SA/Window/GLFW, glfwInit(), L"GLFW init failed!");

		SA_LOG(L"Window System created.", Infos, SA/Window/GLFW);
	}

	void WindowSystem::Destroy()
	{
		glfwTerminate();

		SA_LOG(L"Window System destroyed.", Infos, SA/Window/GLFW);
	}


	bool WindowSystem::QueryRequiredExtensions(std::vector<const char*>& _extensions) const
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

#endif
