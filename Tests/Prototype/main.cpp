// Copyright(c) 2022 Sapphire's Suite. All Rights Reserved.

#include <iostream>

#include <SA/Collections/Debug>
#include <SA/Collections/Window>
using namespace Sa;

int main()
{
//{ Init Logger

	Logger logger;
	Sa::Debug::logger = &logger;

	ConsoleLogStream cslStream;
	logger.Register(cslStream);

	FileLogStream fileStream;
	logger.Register(fileStream);

//}


//{ Init

	// Window

	GLFW::WindowInterface winIntf;
	winIntf.Create();

	WindowCreateInfos infos;
	AWindow* const win = winIntf.CreateWindow(infos);


	// Input

	// GLFW::InputInterface inputIntf;
	// inputIntf.Create();

	// AInputWindowContext* const inputWinContext = inputIntf.CreateInputWindowContext(win);
	// InputContext* const inputContext = inputWinContext->CreateContext();

//}


//{ Loop

#if !SA_CI

	while (!win->ShouldClose())

#endif
	{
		// inputIntf.Update();
	}

//}


//{ Uninit

	// Input

	// inputIntf.Destroy();


	// Window

	winIntf.Destroy();

//}

	return 0;
}
