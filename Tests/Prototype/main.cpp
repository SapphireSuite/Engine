// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <iostream>

#include <SA/Collections/Debug>
using namespace Sa;

#include <SA/Core/Time/Chrono.hpp>

#include <SA/Maths/Transform/Transform.hpp>

#include <SA/Input/GLFW/GLFWInputInterface.hpp>
#include <SA/Input/Base/Key/Bindings/InputKeyAction.hpp>
#include <SA/Input/Base/Key/Bindings/InputKeyRange.hpp>
#include <SA/Input/Base/Axis/Bindings/InputAxisAction.hpp>
#include <SA/Input/Base/Axis/Bindings/InputAxisRange.hpp>

#include <SA/SDK/ECS/Systems/WindowSystem.hpp>
#include <SA/SDK/ECS/Systems/InputSystem.hpp>
#include <SA/SDK/ECS/Systems/Render/RenderSystem.hpp>

// TODO: Remove later.
#include <SA/Render/Vulkan/VkRenderInterface.hpp>
#include <SA/Render/Vulkan/VkRenderGraphicInterface.hpp>
#include <SA/Render/Vulkan/VkRenderContextInterface.hpp>

#include <SA/Render/Vulkan/Device/VkDevice.hpp>
//

//#include <SA/Render/Vulkan/VkRenderInterface.hpp>
//#include <SA/Render/Vulkan/Surface/VkWindowSurface.hpp>
//#include <SA/Render/Vulkan/Surface/VkSurface.hpp>

#include <SA/SDK/Assets/Render/ShaderAsset.hpp>
#include <SA/SDK/ShaderBuilder/GLSL/GLSLShaderBuilder.hpp>
#include <SA/SDK/Assets/Render/TextureAsset.hpp>
//#include <SA/SDK/Assets/Render/ModelAsset.hpp>

//#include <SA/Render/Vulkan/Device/VkCommandPool.hpp>
//#include <SA/Render/Vulkan/Buffers/VkFrameBuffer.hpp>
//#include <SA/Render/Vulkan/Buffers/VkCommandBuffer.hpp>
//#include <SA/Render/Vulkan/Pipeline/VkDescriptorSet.hpp>
//#include <SA/Render/Vulkan/Buffers/VkBuffer.hpp>
//#include <SA/Render/Vulkan/VkRenderFrame.hpp>

//#include <SA/Render/Base/Shader/Bindings/ShaderUBOBinding.hpp>
//#include <SA/Render/Base/Shader/Bindings/ShaderIBOBinding.hpp>


WindowSystem winSys;
AWindow* win = nullptr;


InputSystem inputSys;


RenderSystem renderSys;

// TODO: Remove later.
Vk::RenderInterface* renderIntf = nullptr;
ARenderGraphicInterface* renderGraph = nullptr;
ARenderContextInterface* renderContext = nullptr;

WindowSurfaceHandle winSurface;
RenderSurfaceHandle surface;

RenderPassHandle renderPass;
RenderPassDescriptor renderPassDesc;

ShaderHandle unlitvert;
ShaderHandle unlitfrag;
TextureHandle missText;

//RenderSubSystem* renderSubSys;
//
//Vk::RenderInterface* renderIntf = nullptr;
//ARenderSubInterface* renderSubIntf = nullptr;
//
//
//RenderPipelineDescriptor unlitPipelineDesc;
//ARenderPipeline* unlitPipeline = nullptr;
//
//AStaticMesh* cubeMesh = nullptr;
//ARenderMaterial* cubeMat = nullptr;
//
//TransffPR camTr;
//ACamera* camera = nullptr;

GLSL::ShaderBuilder shaderBuilder;

//Vk::CommandPool cmdPool;
//std::vector<Vk::CommandBuffer> cmdBuffers;
//uint32 imageIndex = 0u;
//
//Vk::Buffer modelUBO;

const Vec2ui winDim{ 1200u, 800u };

struct modelUBOData
{
	CMat4f modelMat = Mat4f::Identity;

	float uvTilling = 1.0f;
	float uvOffset = 0.0f;
};

float deltaTime = 0.0f;


bool bCamEnabled = false;
static float dx = 0.0f;
static float dy = 0.0f;

int32 rightSign = 0;
int32 upSign = 0;
int32 forwardSign = 0;

int main()
{
	// Init.
	{
		Debug::logger.GetChannel(L"SA/Render/Vulkan/VLayers").levelFlags.Remove(LogLevel::Normal);

		// Window.
		{
			winSys.Create<GLFW::WindowInterface>();

			WindowCreateInfos infos;
			infos.dimension = winDim;

			win = winSys.GetInterface()->CreateWindow(infos);
		}


		// Input.
		{
			inputSys.Create<GLFW::InputInterface>();

			AInputWindowContext* const inWinContext = inputSys.GetInterface()->Register(win);
			InputContext* const inputContext = inWinContext->CreateContext();

			inputContext->key.Bind<InputKeyAction>(InputKeyBind{ Key::Esc, KeyState::Pressed }, win, &AWindow::Close);

			inputContext->key.Bind<InputKeyAction>(InputKeyBind{ Key::D, KeyState::Pressed }, []() { rightSign = 1; });
			inputContext->key.Bind<InputKeyAction>(InputKeyBind{ Key::D, KeyState::Released }, [](){ if(rightSign == 1) rightSign = 0; });
			inputContext->key.Bind<InputKeyAction>(InputKeyBind{ Key::A, KeyState::Pressed }, []() { rightSign = -1; });
			inputContext->key.Bind<InputKeyAction>(InputKeyBind{ Key::A, KeyState::Released }, []() { if (rightSign == -1) rightSign = 0; });

			inputContext->key.Bind<InputKeyAction>(InputKeyBind{ Key::E, KeyState::Pressed }, []() { upSign = 1; });
			inputContext->key.Bind<InputKeyAction>(InputKeyBind{ Key::E, KeyState::Released }, []() { if (upSign == 1) upSign = 0; });
			inputContext->key.Bind<InputKeyAction>(InputKeyBind{ Key::Q, KeyState::Pressed }, []() { upSign = -1; });
			inputContext->key.Bind<InputKeyAction>(InputKeyBind{ Key::Q, KeyState::Released }, []() { if (upSign == -1) upSign = 0; });

			inputContext->key.Bind<InputKeyAction>(InputKeyBind{ Key::W, KeyState::Pressed }, []() { forwardSign = 1; });
			inputContext->key.Bind<InputKeyAction>(InputKeyBind{ Key::W, KeyState::Released }, []() { if (forwardSign == 1) forwardSign = 0; });
			inputContext->key.Bind<InputKeyAction>(InputKeyBind{ Key::S, KeyState::Pressed }, []() { forwardSign = -1; });
			inputContext->key.Bind<InputKeyAction>(InputKeyBind{ Key::S, KeyState::Released }, []() { if (forwardSign == -1) forwardSign = 0; });

			inputContext->key.Bind<InputKeyAction>(InputKeyBind{ Key::MouseRight, KeyState::Pressed }, []() {
				bCamEnabled = true;
				win->SetCursorMode(CursorMode::Capture | CursorMode::Hidden);
			});
			inputContext->key.Bind<InputKeyAction>(InputKeyBind{ Key::MouseRight, KeyState::Released }, []() {
				bCamEnabled = false;
				win->SetCursorMode(CursorMode::None);
			});

			inputContext->axis.Bind<InputAxisRange>(Axis::MouseX, [](float _inX) {
				if (!bCamEnabled) return;
				dx -= _inX * winDim.x * deltaTime * 0.25f;
				dx = dx > Maths::Pi ? dx - Maths::Pi : dx < -Maths::Pi ? dx + Maths::Pi : dx;
			});
			inputContext->axis.Bind<InputAxisRange>(Axis::MouseY, [](float _inY) {
				if (!bCamEnabled) return;
				dy -= _inY * winDim.y * deltaTime * 0.25f;
				dy = dy > Maths::Pi ? dy - Maths::Pi : dy < -Maths::Pi ? dy + Maths::Pi : dy;
			});
		}


		// Render
		{
			renderIntf = renderSys.Create<Vk::RenderInterface>(winSys);
			winSurface = renderIntf->CreateWindowSurface(win);

			const std::vector<Vk::GraphicDeviceInfos> deviceInfos = Vk::Device::QuerySuitableDevices(*renderIntf, winSurface);
			renderGraph = renderIntf->CreateGraphicInterface(deviceInfos[0]);
			renderContext = renderGraph->CreateContextInterface();

			surface = renderContext->CreateSurface(winSurface);

			renderPassDesc = RenderPassDescriptor::DefaultSingle(surface.Get());
			renderPass = renderContext->CreateRenderPass(renderPassDesc);

			renderContext->CreateFrameBuffers(surface, renderPass, renderPassDesc);

			//cmdPool.Create(device, device.queueMgr.graphics.GetQueue(0).GetFamilyIndex());

			//for(uint32 i = 0; i < 3; ++i)
			//	cmdBuffers.push_back(cmdPool.Allocate(device, VK_COMMAND_BUFFER_LEVEL_PRIMARY));
		}


		//// UBO
		//{
		//	modelUBOData modelUBOd;
		//	modelUBO.Create(device, sizeof(modelUBOData),
		//		VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
		//		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
		//		VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		//		&modelUBOd);
		//}


		// Assets
		{
			//RenderResourceInitializerHandle resInit = renderContext->CreateResourceInitializer();


			// Shaders
			{
				//// Unlit vert
				//{
				//	const std::string assetName = "Assets/Shaders/unlit_vert.spha";
				//	const std::string resName = "/Engine/Resources/Shaders/Forward/unlit.vert";

				//	ShaderAsset asset(&shaderBuilder);

				//	if (!asset.Load(assetName))
				//	{
				//		if (asset.Import(resName))
				//		{
				//			asset.Save(assetName);
				//		}
				//	}

				//	unlitvert = renderContext->CreateShader(resInit, asset.raw);
				//	////unlitPipelineDesc.AddShader(unlitvert, asset.descriptor);
				//}

				//// Unlit frag
				//{
				//	const std::string assetName = "Assets/Shaders/unlit_frag.spha";
				//	const std::string resName = "/Engine/Resources/Shaders/Forward/unlit.frag";

				//	ShaderAsset asset(&shaderBuilder);

				//	if (!asset.Load(assetName))
				//	{
				//		if (asset.Import(resName))
				//		{
				//			asset.Save(assetName);
				//		}
				//	}

				//	unlitfrag = renderContext->CreateShader(resInit, asset.raw);
				//	////unlitPipelineDesc.AddShader(unlitfrag, asset.descriptor);
				//}
			}


			// Texture
			{
				//const std::string assetName = "Assets/Textures/missing.spha";
				//const std::string resName = "/Engine/Resources/Textures/missing_texture.png";

				//TextureAsset asset;

				//if (!asset.Load(assetName))
				//{
				//	if (asset.Import(resName))
				//	{
				//		asset.Save(assetName);
				//	}
				//}

				//missText = renderContext->CreateTexture(resInit, asset.raw);
			}


			// CUBE.
			{
				//const std::string assetName = "Assets/Meshes/cube.spha";
				//const std::string resName = "/Engine/Resources/Meshes/cube.obj";

				//MeshAsset meshAsset;
				//if (!meshAsset.Load(assetName))
				//{
				//	ModelAsset modelAsset;
				//	if (modelAsset.Import(resName))
				//	{
				//		modelAsset.meshes[0].Save(assetName);
				//		meshAsset = std::move(modelAsset.meshes[0]);
				//	}
				//}

				//cubeMesh = renderSubIntf->CreateStaticMesh(resInit, meshAsset.raw);
			}


			//renderContext->SubmitResourceInitializer(resInit);
			//renderContext->DestroyResourceInitializer(resInit);


			// Pipeline
			{
				//unlitPipelineDesc.SetRenderPass(renderPass, renderPassDesc, 0u);
				//unlitPipelineDesc.shaderInfos.vertexBindingLayout.meshLayout = cubeMesh->GetLayout();

				//unlitPipeline = renderSubIntf->CreatePipeline(unlitPipelineDesc);
			}


			// Material.
			{
				//RenderMaterialCreateInfos infos{ unlitPipeline, &unlitPipelineDesc };
				//infos.AddBinding<IBOBinding>(0u, missText);
				//cubeMat = renderSubIntf->CreateMaterial(infos);
			}


			// Camera
			{
				//camera = renderSubIntf->CreateCamera();
				//
				//camera->SetProjection(Mat4f::MakePerspective(90.0f, 1200.0f / 800.0f));
				//
				//camTr.position = Vec3f(0.0f, 0.0f, 5.0f);
				//camera->SetTransform(camTr);
			}
		}
	}


	// Loop.
	{
		Chrono chrono;

	#if !SA_CI

		while (!win->ShouldClose())

	#endif
		{
			deltaTime = chrono.Restart() * 0.000005f;


			inputSys.Update();

			//// Update Camera
			//if(bCamEnabled)
			//{
			//	if (rightSign)
			//		camTr.position += rightSign * deltaTime * camTr.Right();
			//	if (upSign)
			//		camTr.position += upSign * deltaTime * camTr.Up();
			//	if (forwardSign)
			//		camTr.position += -1 * forwardSign * deltaTime * camTr.Forward();

			//	camTr.rotation = Quatf(cos(dx), 0, sin(dx), 0) * Quatf(cos(dy), sin(dy), 0, 0);

			//	camera->SetTransform(camTr);
			//	//camera->Update(device);
			//}


			/*
			Vk::FrameBuffer& frameBuffer = surface.Begin(device);

			Vk::CommandBuffer& cmdBuffer = cmdBuffers[imageIndex];

			Vk::RenderFrame frame{ cmdBuffer };

			cmdBuffer.Begin();

			renderPass.Begin(cmdBuffer, frameBuffer);

			unlitPipeline.Bind(frame);
			cubeDescSet.Bind(frame, unlitPipeline);
			cubeMesh.Draw(frame);


			renderPass.End(cmdBuffer);

			cmdBuffer.End();

			surface.End(device, { cmdBuffer });

			imageIndex = (imageIndex + 1) % 3;
			*/
		}
	}

	// Uninit
	{
		// Render
		{
			renderGraph->GetDevice()->WaitIdle();

			/*
			camUBO.Destroy(device);
			modelUBO.Destroy(device);

			cubeDescSet.Destroy(device);
			*/

			//renderSubIntf->DestroyCamera(camera);

			////renderSubIntf->DestroyMaterial(cubeMat);

			////renderSubIntf->DestroyPipeline(unlitPipeline);

			//renderSubIntf->DestroyStaticMesh(cubeMesh);

			//renderContext->DestroyTexture(missText);

			//renderContext->DestroyShader(unlitvert);
			//renderContext->DestroyShader(unlitfrag);

			renderContext->DestroyFrameBuffers(surface);

			renderContext->DestroyRenderPass(renderPass);

			renderContext->DestroySurface(surface);

			renderGraph->DestroyContextInterface(renderContext);
			renderIntf->DestroyGraphicInterface(renderGraph);

			renderIntf->DestroyWindowSurface(win, winSurface);

			renderSys.Destroy();
		}


		// Input.
		{
			inputSys.Destroy();
		}


		// Window
		{
			winSys.GetInterface()->DestroyWindow(win);
			winSys.Destroy();
		}
	}

#if !SA_CI

	std::cin.get();

#endif

	return 0;
}
