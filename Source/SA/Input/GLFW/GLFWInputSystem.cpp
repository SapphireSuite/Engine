// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/GLFW/GLFWInputSystem.hpp>

#include <Input/GLFW/GLFWInputWindowContext.hpp>

#include <Window/GLFW/GLFWWindow.hpp>

#if SA_GLFW

namespace Sa::GLFW
{
	AInputWindowContext* InputSystem::InstantiateWindowContext()
	{
		return new GLFW::InputWindowContext{};
	}

	void InputSystem::DeleteWindowContext(AInputWindowContext* _winContext)
	{
		SA_ASSERT(Nullptr, SA/Input/GLFW, _winContext);

		delete _winContext;
	}


	void InputSystem::Create()
	{
		SA_LOG(L"Input System created.", Infos, SA/Input/GLFW);
	}
	
	void InputSystem::Destroy()
	{
		AInputSystem::Destroy();

		SA_LOG(L"Input System destroyed.", Infos, SA/Input/GLFW);
	}


	void InputSystem::Update()
	{
		glfwPollEvents();
	}
}

#endif
