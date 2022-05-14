// Copyright (c) 2022 Sapphire development team. All Rights Reserved.

#include <SA/Collections/Debug>
#include <SA/Support/API/GLFW.hpp>

#include <Input/GLFW/GLFWInputInterface.hpp>

namespace SA::GLFW
{
	void InputInterface::Create()
	{
		AInputInterface::Create();

		SA_LOG(L"Input Interface created.", Infos, SA/Engine/Input/GLFW);
	}
	
	void InputInterface::Destroy()
	{
		AInputInterface::Destroy();

		SA_LOG(L"Input Interface destroyed.", Infos, SA/Engine/Input/GLFW);
	}

	void InputInterface::Clear()
	{
		AInputInterface::Clear();

		mInputWinContexts.Clear(DestroyFunctor<InputWindowContext>());
		
		SA_LOG(L"Input Interface cleared.", Infos, SA/Engine/Input/GLFW);
	}


	void InputInterface::Update()
	{
		glfwPollEvents();
	}


	AInputWindowContext* InputInterface::CreateInputWindowContext(AWindow* _win)
	{
		InputWindowContext* inputWinContext = mInputWinContexts.Emplace();

		inputWinContext->Create(_win);

		return inputWinContext;
	}

	void InputInterface::DestroyInputWindowContext(AInputWindowContext* _winContext)
	{
		SA_ASSERT(Nullptr, SA/Engine/Input/GLFW, _winContext);

		bool bRemoved = mInputWinContexts.Erase(_winContext, DestroyFunctor<InputWindowContext>());

		if(!bRemoved)
			SA_LOG(L"InputWindowContext [" << _winContext << "] not created with this inferface.", Warning, SA/Engine/Input/GLFW);
	}
}
