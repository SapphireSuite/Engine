// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <iostream>

#define LOG(_str) std::cout << _str << std::endl;

#include <SA/Collections/Debug>
using namespace Sa;

#include <SA/Window/GLFW/GLFWWindow.hpp>

#include <SA/Input/Base/Key/Bindings/InputKeyAction.hpp>
#include <SA/Input/Base/Key/Bindings/InputKeyRange.hpp>
#include <SA/Input/Base/Axis/Bindings/InputAxisAction.hpp>
#include <SA/Input/Base/Axis/Bindings/InputAxisRange.hpp>

GLFW::Window win;

InputContext* inputContext = nullptr;

std::shared_ptr<InputKeyBinding> yHoldBind;

int main()
{
	win.Create(1200u, 800);

	inputContext = win.GetInputSystem().CreateContext();

	inputContext->key.Bind<InputKeyAction>(InputKey{ Key::Q, KeyState::Pressed }, []() { SA_LOG("Q Pressed"); });
	inputContext->key.Bind<InputKeyAction>(InputKey{ Key::Q, KeyState::Released }, []() { SA_LOG("Q Released"); });
	inputContext->key.Bind<InputKeyAction>(InputKey{ Key::Esc, KeyState::Pressed }, &win, &GLFW::Window::Close);

	inputContext->key.Bind<InputKeyAction>(InputKey{ Key::Y, KeyState::Pressed }, []() { SA_LOG("Y Pressed:"); });


	inputContext->key.Bind<InputKeyAction>(InputKey{ Key::O, KeyState::Pressed }, []()
	{
		inputContext->axis.Bind<InputAxisRange>(Axis::MouseX, [](float _inX) { SA_LOG("MouseX: " << _inX); });
		inputContext->axis.Bind<InputAxisRange>(Axis::MouseY, [](float _inY) { SA_LOG("MouseY: " << _inY); });
			
		yHoldBind = inputContext->key.Bind<InputKeyRange>(InputKey{ Key::Y, KeyState::Pressed | KeyState::Hold },
			[](float _inX) { SA_LOG("Y Pressed Or Hold:" << _inX); });
	});

	inputContext->key.Bind<InputKeyAction>(InputKey{ Key::P, KeyState::Pressed }, []()
	{
		inputContext->axis.UnBind(Axis::MouseX);
		inputContext->axis.UnBind(Axis::MouseY);

		inputContext->key.UnBind(yHoldBind);
	});


	inputContext->key.Bind<InputKeyAction>(InputKey{ Key::J, KeyState::Pressed }, []() { win.SetWindowMode(WindowMode::Windowed); });
	inputContext->key.Bind<InputKeyAction>(InputKey{ Key::K, KeyState::Pressed }, []() { win.SetWindowMode(WindowMode::FullScreen); });
	inputContext->key.Bind<InputKeyAction>(InputKey{ Key::L, KeyState::Pressed }, []() { win.SetWindowMode(WindowMode::Borderless); });

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