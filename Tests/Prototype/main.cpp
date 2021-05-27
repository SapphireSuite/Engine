// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <iostream>

#define LOG(_str) std::cout << _str << std::endl;

#include <SA/Collections/Debug>
using namespace Sa;

#include <SA/Window/GLFW/GLFW.hpp>
#include <SA/Window/GLFW/GLFWWindow.hpp>

void OnKey(InputKey _key, InputKeyState _state)
{
	SA_LOG("Input: " << _key << ": " << _state);
}

int main()
{
	GLFW::Window win;

	win.Create(1200u, 800);

	win.input.onKey += OnKey;

#if !SA_CI

	while (!win.ShouldClose())

#endif
	{
		GLFW::PollEvents();
	}

	return 0;
}