// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <iostream>

#include <SA/Collections/Debug>
#include <SA/Collections/Window>
#include <SA/Collections/Input>
#include <SA/Collections/Render>
using namespace SA;

#include <SA/Engine/SDK/ShaderBuilder/GLSL/GLSLShaderBuilder.hpp>
#include <SA/Engine/Render/Base/Shader/Descriptors/ShaderDescriptor.hpp>

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
	

	GLSL::ShaderBuilder shBuilder;

	RawShader vertRawSh;
	ShaderDescriptor vertShDesc;
	shBuilder.Build("Resources/Shaders/Forward/unlit.vert", vertRawSh, vertShDesc);

	ARenderResourceInitializer* const resInit = renderContext->CreateResourceInitializer();
	AShader* const vertShader = renderContext->CreateShader(resInit, vertRawSh);

	RenderPipelineLayoutDescriptor pipLayoutDesc;
	pipLayoutDesc.AddShader(vertShDesc);

	ARenderPipelineLayout* const pipLayout = renderContext->CreatePipelineLayout(pipLayoutDesc);


	RenderPipelineDescriptor pipDesc;
	pipDesc.passInfos.SetRenderPass(renderPass, renderPassDesc);
	pipDesc.shaderInfos.AddShader(vertShader, vertShDesc);
	pipDesc.shaderInfos.vertexLayoutDesc.BindVertexComponents<VertexPNTT, VertexPosition, VertexTexture>();

	ARenderPipeline* const pipeline = renderContext->CreatePipeline(pipDesc, pipLayout);


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

		pipeline->Bind(frame);

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
