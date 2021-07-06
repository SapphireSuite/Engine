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

	inputContext->Bind(InputKey{ Key::Q, KeyState::Pressed }, Function<void()>([]() { SA_LOG("Q Pressed"); }));
	inputContext->Bind(InputKey{ Key::Q, KeyState::Released }, Function<void()>([]() { SA_LOG("Q Released"); }));
	inputContext->Bind(InputKey{ Key::Esc, KeyState::Pressed }, Function<void()>(&win, &GLFW::Window::Close));

	inputContext->Bind(InputKey{ Key::T, KeyState::Pressed }, Function<void()>([]() { SA_LOG("T Pressed"); }));
	inputContext->Bind(InputKey{ Key::T, KeyState::Released }, Function<void()>([]() { SA_LOG("T Released"); }));

	inputContext->Bind(InputKey{ Key::Y, KeyState::Pressed }, Function<void()>([]() { SA_LOG("Y Pressed"); }));
	inputContext->Bind(InputKey{ Key::Y, KeyState::Released }, Function<void()>([]() { SA_LOG("Y Released"); }));

	inputContext->Bind(InputAxis{ Axis::MouseX }, Function<void(float)>([](float _inX) { SA_LOG("MouseX: " << _inX); }));
	inputContext->Bind(InputAxis{ Axis::MouseY }, Function<void(float)>([](float _inY) { SA_LOG("MouseY: " << _inY); }));


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