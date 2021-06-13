// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <iostream>

#define LOG(_str) std::cout << _str << std::endl;

#include <SA/Collections/Debug>
using namespace Sa;

#include <SA/Window/GLFW/GLFW.hpp>
#include <SA/Window/GLFW/GLFWWindow.hpp>

int main()
{
	GLFW::Window win;

	win.Create(1200u, 800);

	InputContext* inputContext = win.input.CreateContext();

	inputContext->Bind(InputKey{ Key::Q, KeyState::Pressed }, Function<void()>([]() { SA_LOG("Q Pressed"); }));
	inputContext->Bind(InputKey{ Key::Q, KeyState::Released }, Function<void()>([]() { SA_LOG("Q Released"); }));
	
#if !SA_CI

	while (!win.ShouldClose())

#endif
	{
		GLFW::PollEvents();
	}

	return 0;
}