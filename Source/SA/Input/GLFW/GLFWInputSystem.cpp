// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/GLFW/GLFWInputSystem.hpp>

#include <Core/Algorithms/Equals.hpp>

#if SA_GLFW

namespace Sa
{
	void GLFWInputSystem::WindowKeyCallback(const InputKey& _inKey)
	{
		Process(_inKey);
	}

	void GLFWInputSystem::CursorPositionCallback(const Vec2ui& _windowSize, const Vec2f& _mousePos)
	{
		if(!Sa::Equals(_mousePos.x, mSavedMousePos.x))
			Process(InputAxis{ Axis::MouseX, (_mousePos.x - mSavedMousePos.x) / _windowSize.x });
		
		if (!Sa::Equals(_mousePos.y, mSavedMousePos.y))
			Process(InputAxis{ Axis::MouseY, (_mousePos.y - mSavedMousePos.y) / _windowSize.y });

		mSavedMousePos = _mousePos;
	}


	void GLFWInputSystem::Create(GLFWwindow* _handle)
	{
		glfwSetKeyCallback(_handle, GLFW::WindowKeyCallback);
		glfwSetCursorPosCallback(_handle, GLFW::CursorPositionCallback);


		// Init first cursor position.
		{
			double mouseX = 0.0;
			double mouseY = 0.0;

			glfwGetCursorPos(_handle, &mouseX, &mouseY);

			GLFW::CursorPositionCallback(_handle, mouseX, mouseY);
		}
	}

	void GLFWInputSystem::Destroy()
	{
	}


	void GLFWInputSystem::Update()
	{
		glfwPollEvents();
	}
}

#endif
