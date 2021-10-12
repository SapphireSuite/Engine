// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Input/GLFW/GLFWInputInterface.hpp>

#include <Input/GLFW/GLFWInputWindowContext.hpp>

#include <Window/GLFW/GLFWWindow.hpp>

#if SA_GLFW

namespace Sa::GLFW
{
	AInputWindowContext* InputInterface::InstantiateWindowContext()
	{
		return new GLFW::InputWindowContext{};
	}

	void InputInterface::DeleteWindowContext(AInputWindowContext* _winContext)
	{
		SA_ASSERT(Nullptr, SA/Input/GLFW, _winContext);

		delete _winContext;
	}


	void InputInterface::Create()
	{
		SA_LOG(L"Input Interface created.", Infos, SA/Input/GLFW);
	}
	
	void InputInterface::Destroy()
	{
		AInputInterface::Destroy();

		SA_LOG(L"Input Interface destroyed.", Infos, SA/Input/GLFW);
	}


	void InputInterface::Update()
	{
		glfwPollEvents();
	}
}

#endif
