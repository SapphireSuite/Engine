// Copyright(c) 2022 Sapphire's Suite. All Rights Reserved.

#include <iostream>

#include <SA/Collections/Debug>
#include <SA/Collections/Window>
#include <SA/Collections/Input>
#include <SA/Collections/Render>
using namespace Sa;

int main()
{
//{ Init

	// Logger
	Logger logger;
	Sa::Debug::logger = &logger;

	ConsoleLogStream cslStream;
	logger.Register(cslStream);

	FileLogStream fileStream;
	logger.Register(fileStream);


	// Window
	GLFW::WindowInterface winIntf;
	winIntf.Create();

	WindowCreateInfos infos;
	AWindow* const win = winIntf.CreateWindow(infos);


	// Input
	GLFW::InputInterface inputIntf;
	inputIntf.Create();

	AInputWindowContext* const inputWinContext = inputIntf.CreateInputWindowContext(win);
	// InputContext* const inputContext = inputWinContext->CreateContext();


	// Render
	Vk::RenderInterface renderIntf;
	renderIntf.Create(&winIntf);

	AWindowSurface* const winSurface = renderIntf.CreateWindowSurface(win);
	
	const PolymorphicVector<ARenderDeviceInfos> deviceInfos = renderIntf.QueryDevices(winSurface);

	ARenderDevice* const renderDevice = renderIntf.CreateDevice(deviceInfos[0]);

	ARenderContext* const renderContext = renderDevice->CreateRenderContext();

	ARenderSurface* const surface = renderContext->CreateSurface(winSurface);

//}


//{ Loop

#if !SA_CI

	while (!win->ShouldClose())

#endif
	{
		inputIntf.Update();
	}

//}


//{ Uninit

	// Render
	renderIntf.Destroy();

	// Input
	inputIntf.Destroy();


	// Window
	winIntf.Destroy();

//}

	return 0;
}
