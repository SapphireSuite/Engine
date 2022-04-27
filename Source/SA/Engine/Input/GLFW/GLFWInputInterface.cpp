// Copyright (c) 2022 Sapphire development team. All Rights Reserved.

#include <SA/Collections/Debug>
#include <SA/Support/API/GLFW.hpp>

#include <Input/GLFW/GLFWInputInterface.hpp>

namespace Sa::GLFW
{
	void InputInterface::Create()
	{
		AInputInterface::Create();

		SA_LOG(L"Input Interface created.", Infos, SA/Windowing/Input/GLFW);
	}
	
	void InputInterface::Destroy()
	{
		AInputInterface::Destroy();

		SA_LOG(L"Input Interface destroyed.", Infos, SA/Windowing/Input/GLFW);
	}

	void InputInterface::Clear()
	{
		AInputInterface::Clear();

		for (auto it = mInputWinContexts.begin(); it != mInputWinContexts.end(); ++it)
			it->Destroy();

		mInputWinContexts.clear();
	}


	void InputInterface::Update()
	{
		glfwPollEvents();
	}


	AInputWindowContext* InputInterface::CreateInputWindowContext(AWindow* _win)
	{
		InputWindowContext& inputWinContext = mInputWinContexts.emplace_back();

		inputWinContext.Create(_win);

		return &inputWinContext;
	}

	void InputInterface::DestroyInputWindowContext(AInputWindowContext* _winContext)
	{
		SA_ASSERT(Nullptr, SA/Windowing/Input/GLFW, _winContext);

		for (auto it = mInputWinContexts.begin(); it != mInputWinContexts.end(); ++it)
		{
			if (&*it == _winContext)
			{
				_winContext->Destroy();
				mInputWinContexts.erase(it);
				
				return;
			}
		}

		SA_LOG(L"InputWindowContext [" << _winContext << "] not created with this inferface.", Warning, SA/Windowing/Input/GLFW);
	}
}
