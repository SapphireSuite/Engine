// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <iostream>

#define LOG(_str) std::cout << _str << std::endl;

#include <SA/Collections/Debug>
using namespace Sa;

#include <SA/Window/GLFW/GLFWWindow.hpp>
#include <SA/Window/GLFW/GLFWWindowSystem.hpp>

#include <SA/Input/GLFW/GLFWInputSystem.hpp>
#include <SA/Input/Base/Key/Bindings/InputKeyAction.hpp>
#include <SA/Input/Base/Key/Bindings/InputKeyRange.hpp>
#include <SA/Input/Base/Axis/Bindings/InputAxisAction.hpp>
#include <SA/Input/Base/Axis/Bindings/InputAxisRange.hpp>

#include <SA/Render/Vulkan/VkRenderSystem.hpp>
#include <SA/Render/Vulkan/VkRenderInstance.hpp>

GLFW::WindowSystem winSys;
GLFW::Window win;

GLFW::InputSystem inputSys;

Vk::RenderSystem renderSys;
Vk::RenderInstance renderInst;


int main()
{
	// Init.
	{
		// Window.
		{
			winSys.Create();

			GLFW::Window::CreateInfos infos;
			infos.dimension = Vec2ui{ 1200u, 800u };

			win.Create(infos);
		}


		// Input.
		{
			inputSys.Create();

			AInputWindowContext* const inWinContext = inputSys.Register(&win);
			InputContext* const inputContext = inWinContext->Create();

			inputContext->key.Bind<InputKeyAction>(InputKeyBind{ Key::Esc, KeyState::Pressed }, &win, &GLFW::Window::Close);

			//inputContext->axis.Bind<InputAxisRange>(Axis::MouseX, [](float _inX) { SA_LOG("MouseX: " << _inX); });
			//inputContext->axis.Bind<InputAxisRange>(Axis::MouseY, [](float _inY) { SA_LOG("MouseY: " << _inY); });
		}


		// Render
		{
			renderSys.Create();
			renderInst.Create(winSys);
		}
	}


	// Loop.
	{
	#if !SA_CI

		while (!win.ShouldClose())

	#endif
		{
			inputSys.Update();
		}
	}


	// Uninit
	{
		// Render
		{
			renderInst.Destroy();
			renderSys.Destroy();
		}


		// Input.
		{
			inputSys.Destroy();
		}


		// Window
		{
			win.Destroy();
			winSys.Destroy();
		}


#if SA_LOGGING

		Debug::logger.Join();

#endif
	}

#if !SA_CI

	std::cin.get();

#endif

	return 0;
}