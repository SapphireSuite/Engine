// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <iostream>

#include <SA/Collections/Debug>
#include <SA/Collections/Window>
#include <SA/Collections/Input>
#include <SA/Collections/Render>
using namespace SA;

#include "UnlitRenderer.hpp"

int main()
{
//{ Init

	// Logger
	Logger logger;
	SA::Debug::logger = &logger;

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

	// AInputWindowContext* const inputWinContext = inputIntf.CreateInputWindowContext(win);
	// InputContext* const inputContext = inputWinContext->CreateContext();


	// Render
	VK::RenderInterface renderIntf;
	renderIntf.Create(&winIntf);

	AWindowSurface* const winSurface = renderIntf.CreateWindowSurface(win);
	
	const PolymorphicVector<ARenderDeviceInfos> deviceInfos = renderIntf.QueryDevices(winSurface);
	ARenderDevice* const renderDevice = renderIntf.CreateDevice(deviceInfos[0]);
	ARenderContext* const renderContext = renderDevice->CreateRenderContext();

	ARenderSurface* const surface = renderContext->CreateSurface(winSurface);

	const RenderPassDescriptor renderPassDesc = RenderPassDescriptor::DefaultSingle(surface);

	const Rect2Dui renderRect = { { 0, 0 }, surface->GetExtent() };
	ARenderPass* const renderPass = renderContext->CreateRenderPass(renderPassDesc);
	
	renderContext->CreateFrameBuffers(surface, renderPass, renderPassDesc);
	


	ARenderResourceInitializer* const resInit = renderContext->CreateResourceInitializer();


	SDK::AssetMgr assetMgr;


	UnlitRenderer unlitRender;
	unlitRender.Create(assetMgr, renderContext, resInit, renderPass, renderPassDesc, 0u);

	ATexture* const missingTexture = LoadImportSaveCreateTexture(
		assetMgr,
		renderContext,
		resInit,
		"Bin/Assets/Textures/missing_texture.spha",
		"Resources/Textures/missing_texture.png"
	);


	MaterialBindingData unlitBindData;
	unlitBindData.Add<IBOBinding>({ "albedo" }, missingTexture);
	ARenderMaterial* const unlitMat = renderContext->CreateMaterial(unlitRender.pipLayout, unlitRender.pipLayoutDesc, unlitBindData);
	// renderContext->BindMaterialData(unlitMat, unlitBindData);


	// AStaticMesh* const cubeMesh = LoadImportSaveCreateMesh(
	// 	renderContext,
	// 	resInit,
	// 	"Bin/Assets/Meshes/cube.spha",
	// 	"Resources/Meshes/cube.obj"
	// );


	renderContext->SubmitResourceInitializer(resInit);
	renderContext->DestroyResourceInitializer(resInit);


//}


//{ Loop

	SA_LOG("Start Game loop.");


#if !SA_CI

	while (!win->ShouldClose())

#endif
	{
		inputIntf.Update();

		ARenderFrame& frame = renderContext->BeginSurface(surface);

		renderPass->Begin(frame, renderRect);

		unlitRender.pipeline->Bind(frame);

		renderPass->End(frame);

		renderContext->EndSurface(surface);
	}


	SA_LOG("End Game loop.");

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
