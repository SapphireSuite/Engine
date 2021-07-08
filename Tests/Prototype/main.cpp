// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <iostream>

#define LOG(_str) std::cout << _str << std::endl;

#include <SA/Collections/Debug>
using namespace Sa;

#include <SA/Window/GLFW/GLFWWindow.hpp>

int main()
{
	GLFW::Window win;

	win.Create(1200u, 800);

	InputContext* const inputContext = win.GetInputSystem().CreateContext();

	inputContext->key.Bind<InputKeyAction>(InputKey{ Key::Q, KeyState::Pressed }, []() { SA_LOG("Q Pressed"); });
	inputContext->key.Bind<InputKeyAction>(InputKey{ Key::Q, KeyState::Released }, []() { SA_LOG("Q Released"); });
	inputContext->key.Bind<InputKeyAction>(InputKey{ Key::Esc, KeyState::Pressed }, &win, &GLFW::Window::Close);

	//inputContext->Bind<InputAxisRange>(Axis::MouseX, [](float _inX) { SA_LOG("MouseX: " << _inX); });
	//inputContext->Bind<InputAxisRange>(Axis::MouseY, [](float _inY) { SA_LOG("MouseY: " << _inY); });

	inputContext->key.Bind<InputKeyAction>(InputKey{ Key::Y, KeyState::Pressed }, []() { SA_LOG("Y Pressed:"); });
	inputContext->key.Bind<InputKeyRange>(InputKey{ Key::Y, KeyState::Pressed | KeyState::Hold },
		[](float _inX) { SA_LOG("Y Pressed Or Hold:" << _inX); });


#if !SA_CI

	while (!win.ShouldClose())

#endif
	{
		win.Update();
	}

#if SA_LOGGING

	Debug::logger.Join(ThreadJoinMode::Abandon);

#endif

	return 0;
}