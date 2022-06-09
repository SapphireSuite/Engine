// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <iostream>

#include <SA/Collections/Debug>
#include <SA/Collections/Window>
#include <SA/Collections/Input>
#include <SA/Collections/Render>
using namespace SA;

#include "UnlitRenderer.hpp"

#include <SA/Engine/SDK/MaterialBuilder/Graph/PBRMaterialGraph.hpp>

#include <SA/Engine/SDK/MaterialBuilder/Graph/Node/Scalar/MaterialScalarValueNode.hpp>
#include <SA/Engine/SDK/MaterialBuilder/Graph/Node/Scalar/MaterialNodeScalarLink.hpp>


#include <SA/Engine/SDK/MaterialBuilder/Graph/Node/Color/MaterialColorValueNode.hpp>
#include <SA/Engine/SDK/MaterialBuilder/Graph/Node/Color/MaterialTextureValueNode.hpp>
#include <SA/Engine/SDK/MaterialBuilder/Graph/Node/Color/MaterialNodeColorLink.hpp>
#include <SA/Engine/SDK/MaterialBuilder/Graph/Node/Color/MaterialNodeColorSingleComponentLink.hpp>

#include <SA/Engine/SDK/MaterialBuilder/Graph/Node/Instructions/MaterialOpAddNode.hpp>

int main()
{
	SDK::PBRMaterialGraph pbrGraph;

	// Scalar
	{
		auto s1 = std::make_shared<SDK::MaterialScalarValueNode>(6.45f);
		auto l1 = std::make_shared<SDK::MaterialNodeScalarLink>(s1);

		auto s2 = std::make_shared<SDK::MaterialScalarValueNode>(8.654f);
		auto l2 = std::make_shared<SDK::MaterialNodeScalarLink>(s2);
		
		auto c3 = std::make_shared<SDK::MaterialColorValueNode>(Color{ 0.25f, 0.47f, 0.98f, 1.0f});
		auto l3 = std::make_shared<SDK::MaterialNodeColorSingleComponentLink>(c3,
			SDK::MaterialNodeColorSingleComponentLink::ColorComponent::G);

		auto add = std::make_shared<SDK::MaterialOpAddScalarNode>();

		add->entries.AddEntry(l1);
		add->entries.AddEntry(l2);
		add->entries.AddEntry(l3);
	}

	// Color.
	{
		auto c1 = std::make_shared<SDK::MaterialColorValueNode>(Color{ 0.25f, 0.47f, 0.98f, 1.0f});
		auto l1 = std::make_shared<SDK::MaterialNodeColorLink>(c1);

		auto t2 = std::make_shared<SDK::MaterialTextureValueNode>();
		auto l2 = std::make_shared<SDK::MaterialNodeColorLink>(t2);


		auto add = std::make_shared<SDK::MaterialOpAddColorNode>();

		add->entries.AddEntry(l1);
		add->entries.AddEntry(l2);
	}

	// auto c1 = std::make_shared<SDK::MaterialNodeInputColor>();
	// c1->color = Color::blue;

	// auto t1 = std::make_shared<SDK::MaterialValueTextureNode>();
	// auto t2 = std::make_shared<SDK::MaterialValueTextureNode>();

	// auto s1 = std::make_shared<SDK::MaterialValueScalarNode>(5.2f);
	// auto s1Link = SDK::MaterialNodeScalarLink(); s1Link.node = s1;

	// auto s2 = std::make_shared<SDK::MaterialValueScalarNode>(8.45f);
	// auto s2Link = SDK::MaterialNodeScalarLink(); s2Link.node = s1;

	// auto sAdd = std::make_shared<SDK::MaterialOpAddNode<SDK::MaterialNodeScalarLink>>();

	// sAdd->inputs.AddEntry(s1Link);
	// sAdd->inputs.AddEntry(s2Link);

	// auto add = std::make_shared<SDK::MaterialOpAddNode<MaterialNodeColorLink>>();
	


	// pbrGraph.baseColor = std::make_shared<SDK::MaterialNodeResult>();
	// pbrGraph.baseColor->CreateOperation<SDK::MaterialNodeOpAdd>({ t1, t2 });

	return 0;






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
	


	// ARenderResourceInitializer* const resInit = renderContext->CreateResourceInitializer();


	SDK::AssetMgr assetMgr;

	auto cubeAsset = assetMgr.LoadOrImport<SDK::ModelAsset>("Bin/Meshes/cube.spha", "Resources/Meshes/cube.obj");

	cubeAsset.Unload();

	// UnlitRenderer unlitRender;
	// unlitRender.Create(assetMgr, renderContext, resInit, renderPass, renderPassDesc, 0u);

	// ATexture* const missingTexture = LoadImportSaveCreateTexture(
	// 	assetMgr,
	// 	renderContext,
	// 	resInit,
	// 	"Bin/Assets/Textures/missing_texture.spha",
	// 	"Resources/Textures/missing_texture.png"
	// );


	// MaterialBindingData unlitBindData;
	// unlitBindData.Add<IBOBinding>({ "albedo" }, missingTexture);
	// ARenderMaterial* const unlitMat = renderContext->CreateMaterial(unlitRender.pipLayout, unlitRender.pipLayoutDesc, unlitBindData);
	// // renderContext->BindMaterialData(unlitMat, unlitBindData);


	// AStaticMesh* const cubeMesh = LoadImportSaveCreateMesh(
	// 	assetMgr,
	// 	renderContext,
	// 	resInit,
	// 	"Bin/Assets/Meshes/cube.spha",
	// 	"Resources/Meshes/cube.obj"
	// );


	// renderContext->SubmitResourceInitializer(resInit);
	// renderContext->DestroyResourceInitializer(resInit);

	// assetMgr.Clear();

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

		// unlitRender.pipeline->Bind(frame);

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
