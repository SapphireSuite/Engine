// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/GLFW/GLFWInputWindowContext.hpp>

#include <Window/GLFW/GLFWWindow.hpp>

#include <Core/Algorithms/Equals.hpp>

namespace Sa::GLFW
{
	InputWindowContext::InputWindowContext(Window* _win)
	{
		SA_ASSERT(Nullptr, SA/Input/GLFW, _win);

		GLFWwindow* const winHandle = _win->GetHandle();
		SA_ASSERT(Nullptr, SA/Input/GLFW, winHandle);

		_win->inputWinContext = this;

		glfwSetKeyCallback(winHandle, GLFW::WindowKeyCallback);
		glfwSetCursorPosCallback(winHandle, GLFW::CursorPositionCallback);


		// Init first cursor position.
		{
			double mouseX = 0.0;
			double mouseY = 0.0;

			glfwGetCursorPos(winHandle, &mouseX, &mouseY);

			GLFW::CursorPositionCallback(winHandle, mouseX, mouseY);
		}
	}


	void InputWindowContext::WindowKeyCallback(const InputRawKey& _inRawKey)
	{
		Process(_inRawKey);
	}

	void InputWindowContext::CursorPositionCallback(const Vec2ui& _windowSize, const Vec2f& _mousePos)
	{
		if (!Sa::Equals(_mousePos.x, mSavedMousePos.x))
			Process(InputAxis{ Axis::MouseX, (_mousePos.x - mSavedMousePos.x) / _windowSize.x });

		if (!Sa::Equals(_mousePos.y, mSavedMousePos.y))
			Process(InputAxis{ Axis::MouseY, (_mousePos.y - mSavedMousePos.y) / _windowSize.y });

		mSavedMousePos = _mousePos;
	}
}
