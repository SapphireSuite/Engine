// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/GLFW/GLFWInputWindowContext.hpp>
#include <Input/GLFW/GLFWInputMapping.hpp>

#include <Window/GLFW/GLFWWindow.hpp>

#include <Core/Algorithms/Equals.hpp>

#if SA_GLFW

namespace Sa::GLFW
{
	void WindowKeyCallback(struct GLFWwindow* _handle, int _key, int _scancode, int _action, int _mods)
	{
		(void)_scancode;
		(void)_mods;

		GLFW::Window* const win = static_cast<GLFW::Window*>(glfwGetWindowUserPointer(_handle));
		SA_ASSERT(Nullptr, SA/Window/GLFW, win);
		SA_ASSERT(Nullptr, SA/Window/GLFW, win->inputWinContext);


		auto keyIt = gGlfwToEngineInputMap.find(_key);

#if SA_DEBUG

		if (keyIt == gGlfwToEngineInputMap.end())
		{
			SA_LOG(L"Key [" << _key << "] not registered in input map.", Warning, SA/Window/GLFW);

			win->inputWinContext->WindowKeyCallback(InputKey{ Key::Esc, KeyState::Pressed });

			return;
		}

#endif

		const InputKey key{ keyIt->second, GetKeyState(_action) };

		win->inputWinContext->WindowKeyCallback(key);
	}

	void CursorPositionCallback(GLFWwindow* _handle, double _posX, double _posY)
	{
		GLFW::Window* const win = static_cast<GLFW::Window*>(glfwGetWindowUserPointer(_handle));
		SA_ASSERT(Nullptr, SA/Window/GLFW, win);
		SA_ASSERT(Nullptr, SA/Window/GLFW, win->inputWinContext);

		win->inputWinContext->CursorPositionCallback(win->GetSize(), Vec2d{ _posX, _posY });
	}


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


	void InputWindowContext::WindowKeyCallback(const InputKey& _inRawKey)
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

#endif
