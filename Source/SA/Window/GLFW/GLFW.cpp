// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Window/GLFW/GLFW.hpp>

#include <Collections/Debug>

#if SA_GLFW

#include <GLFW/glfw3.h>

namespace Sa::GLFW
{
	static uint32 gInitCount = 0u;

	void ErrorCallback(int32 error, const char* description)
	{
		SA_LOG(L"GLFW Error [" << error << L"]:" << description, Error, Window/GLFW);
	}


	void Init()
	{
		// Already init.
		if (gInitCount++ > 0)
			return;

		glfwSetErrorCallback(ErrorCallback);

		bool bInit = glfwInit();

		(void)bInit;
		SA_ASSERT(Default, Window/GLFW, bInit, L"GLFW init failed!");
	}

	void UnInit()
	{
		// Not last instance.
		if (--gInitCount > 0)
			return;

		glfwTerminate();
	}


	void PollEvents()
	{
		glfwPollEvents();
	}
}

#endif
