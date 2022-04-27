// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SA/Collections/Debug>

#include <Input/GLFW/GLFWInputWindowContext.hpp>

#include <HI/Cast.hpp>
#include <Window/GLFW/GLFWWindow.hpp>

namespace Sa::GLFW
{
	void WindowKeyCallback(GLFWwindow* _handle, int _key, int _scancode, int _action, int _mods)
	{
	}
	
	void WindowMouseCallback(GLFWwindow* _handle, int _button, int _action, int _mods)
	{
	}

	void CursorPositionCallback(GLFWwindow* _handle, double _posX, double _posY)
	{
	}


	void InputWindowContext::Create(AWindow* _win)
	{
		AInputWindowContext::Create(_win);

		mWindow = Cast<Window>(_win);
		SA_ASSERT(Nullptr, SA/Engine/Input/GLFW, mWindow, L"Window must be of type GLFW::Window");
		SA_ASSERT(Default, SA/Engine/Input/GLFW, mWindow->inputWinContext == nullptr,
			L"Window already has an InputWindowContext bound!");

		mWindow->inputWinContext = this;

		GLFWwindow* const winHandle = mWindow->GetHandle();
		SA_ASSERT(Nullptr, SA/Engine/Input/GLFW, winHandle, L"Window must be created. Call window->Create().");


		// Set Callbacks.
		glfwSetKeyCallback(winHandle, GLFW::WindowKeyCallback);
		glfwSetMouseButtonCallback(winHandle, GLFW::WindowMouseCallback);
		glfwSetCursorPosCallback(winHandle, GLFW::CursorPositionCallback);


		// Init first cursor position.
		{
			double mouseX = 0.0;
			double mouseY = 0.0;

			glfwGetCursorPos(winHandle, &mouseX, &mouseY);

			GLFW::CursorPositionCallback(winHandle, mouseX, mouseY);
		}


		SA_LOG(L"Input Window Context created.", Infos, SA/Engine/Input/GLFW);
	}
	
	void InputWindowContext::Destroy()
	{
		AInputWindowContext::Destroy();

		if (mWindow->inputWinContext) // null if window already destroyed.
		{
			GLFWwindow* const winHandle = mWindow->GetHandle();
			SA_ASSERT(Nullptr, SA/Engine/Input/GLFW, winHandle,
				L"Window must be created. Call window->Create().");


			// Clear callbacks.
			glfwSetKeyCallback(winHandle, nullptr);
			glfwSetMouseButtonCallback(winHandle, nullptr);
			glfwSetCursorPosCallback(winHandle, nullptr);

			mWindow->inputWinContext = nullptr;
		}

		mWindow = nullptr;


		SA_LOG(L"Input Window Context destroyed.", Infos, SA/Engine/Input/GLFW);
	}
}
