// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <iostream>

#include <SA/Collections/Debug>
using namespace Sa;

#include <SA/Core/Time/Chrono.hpp>

#include <SA/Maths/Transform/Transform.hpp>

#include <SA/Window/GLFW/GLFWWindow.hpp>
#include <SA/Window/GLFW/GLFWWindowSystem.hpp>

#include <SA/Input/GLFW/GLFWInputSystem.hpp>
#include <SA/Input/Base/Key/Bindings/InputKeyAction.hpp>
#include <SA/Input/Base/Key/Bindings/InputKeyRange.hpp>
#include <SA/Input/Base/Axis/Bindings/InputAxisAction.hpp>
#include <SA/Input/Base/Axis/Bindings/InputAxisRange.hpp>

#include <SA/Render/Vulkan/VkRenderSystem.hpp>

#include <SA/SDK/Assets/Shader/ShaderAsset.hpp>

//#include <SA/Render/Vulkan/Device/VkCommandPool.hpp>
//#include <SA/Render/Vulkan/Buffers/VkFrameBuffer.hpp>
//#include <SA/Render/Vulkan/Buffers/VkCommandBuffer.hpp>
//#include <SA/Render/Vulkan/Mesh/VkStaticMesh.hpp>
//#include <SA/Render/Vulkan/Pipeline/VkDescriptorSet.hpp>
//#include <SA/Render/Vulkan/Buffers/VkBuffer.hpp>
//#include <SA/Render/Vulkan/Texture/VkTexture.hpp>
//#include <SA/Render/Vulkan/VkRenderFrame.hpp>

//#include <SA/Render/Base/Shader/Bindings/ShaderUBOBinding.hpp>
//#include <SA/Render/Base/Shader/Bindings/ShaderIBOBinding.hpp>

//#include <SA/SDK/Assets/ModelAsset.hpp>
//#include <SA/SDK/Assets/TextureAsset.hpp>

GLFW::WindowSystem winSys;
GLFW::Window win;

GLFW::InputSystem inputSys;

Vk::RenderSystem renderSys;
ARenderDevice* device = nullptr;
ARenderSurface* surface = nullptr;
RenderPassDescriptor renderPassDesc;
ARenderPass* renderPass = nullptr;
RenderPipelineCreateInfos unlitPipelineInfos{ *renderPass, renderPassDesc };
ARenderPipeline* unlitPipeline = nullptr;

AShader* unlitvert = nullptr;
AShader* unlitfrag = nullptr;

//Vk::CommandPool cmdPool;
//std::vector<Vk::CommandBuffer> cmdBuffers;
//uint32 imageIndex = 0u;
//
//Vk::StaticMesh cubeMesh;
//Vk::DescriptorSet cubeDescSet;
//Vk::Buffer camUBO;
//Vk::Buffer modelUBO;
//Vk::Texture missText;

const Vec2ui winDim{ 1200u, 800u };


struct camUBOData
{
	CMat4f proj = Mat4f::Identity;
	CMat4f viewInv = Mat4f::Identity;
	Vec3f viewPosition;
};

TransffPR camTr;
camUBOData camUBOd;

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
			winSys.Create();

			GLFW::Window::CreateInfos infos;
			infos.dimension = winDim;

			win.Create(infos);
		}


		// Input.
		{
			inputSys.Create();

			AInputWindowContext* const inWinContext = inputSys.Register(&win);
			InputContext* const inputContext = inWinContext->CreateContext();

			inputContext->key.Bind<InputKeyAction>(InputKeyBind{ Key::Esc, KeyState::Pressed }, &win, &GLFW::Window::Close);

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
				win.SetCursorMode(CursorMode::Capture | CursorMode::Hidden);
			});
			inputContext->key.Bind<InputKeyAction>(InputKeyBind{ Key::MouseRight, KeyState::Released }, []() {
				bCamEnabled = false;
				win.SetCursorMode(CursorMode::None);
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
			renderSys.Create(winSys);
			surface = renderSys.CreateWindowSurface(win);
			
			const std::vector<Vk::GraphicDeviceInfos> deviceInfos = Vk::Device::QuerySuitableDevices(renderSys, surface->AsPtr<Vk::Surface>());
			device = renderSys.CreateDevice(deviceInfos[0]);

			surface->Create(device);

			renderPassDesc = RenderPassDescriptor::DefaultSingle(surface);
			renderPass = renderSys.CreateRenderPass(device, renderPassDesc);

			surface->CreateFrameBuffers(device, renderPass, renderPassDesc);

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


		//	camTr.position = Vec3f(0.0f, 0.0f, 5.0f);
		//	camUBOd.proj = Mat4f::MakePerspective(90.0f, 1200.0f / 800.0f);
		//	camUBOd.viewInv = camTr.Matrix().GetInversed();
		//	camUBOd.viewPosition = camTr.position;
		//	camUBO.Create(device, sizeof(camUBOData),
		//		VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
		//		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
		//		VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		//		&camUBOd);
		//}


		// Assets
		{

			//// Submit
			//ResourceHolder resHolder;
			//cmdBuffers[0].Begin();



			//// CUBE.
			//{
			//	const std::string assetName = "Assets/Meshes/cube.spha";
			//	const std::string resName = "/Engine/Resources/Meshes/cube.obj";

			//	MeshAsset meshAsset;
			//	if (!meshAsset.Load(assetName))
			//	{
			//		ModelAsset modelAsset;
			//		if (modelAsset.Import(resName))
			//		{
			//			modelAsset.meshes[0].Save(assetName);
			//			meshAsset = std::move(modelAsset.meshes[0]);
			//		}
			//	}

			//	cubeMesh.Create(device, cmdBuffers[0], resHolder, meshAsset.raw);
			//}




			//// Texture
			//{
			//	const std::string assetName = "Assets/Textures/missing.spha";
			//	const std::string resName = "/Engine/Resources/Textures/missing_texture.png";

			//	TextureAsset asset;

			//	if (!asset.Load(assetName))
			//	{
			//		if (asset.Import(resName))
			//		{
			//			asset.Save(assetName);
			//		}
			//	}

			//	missText.Create(device, cmdBuffers[0], resHolder, asset.raw);
			//}



			//cmdBuffers[0].End();

			//VkCommandBuffer bbb = cmdBuffers[0];

			//// Submit commands.
			//VkSubmitInfo submitInfo{};
			//submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			//submitInfo.pNext = nullptr;
			//submitInfo.waitSemaphoreCount = 0u;
			//submitInfo.pWaitSemaphores = nullptr;
			//submitInfo.pWaitDstStageMask = nullptr;
			//submitInfo.commandBufferCount = 1u;
			//submitInfo.pCommandBuffers = &bbb;
			//submitInfo.signalSemaphoreCount = 0u;
			//submitInfo.pSignalSemaphores = nullptr;

			//vkQueueSubmit(device.queueMgr.transfer.GetQueue(0), 1, &submitInfo, VK_NULL_HANDLE);
			//vkQueueWaitIdle(device.queueMgr.transfer.GetQueue(0));

			//resHolder.FreeAll();


			// Shaders
			{
				// Unlit vert
				{
					const std::string assetName = "Assets/Shaders/unlit_vert.spha";
					const std::string resName = "/Engine/Resources/Shaders/Forward/unlit.vert";

					ShaderAsset asset;

					if (!asset.Load(assetName))
					{
						if (asset.Import(resName))
						{
							asset.Save(assetName);
						}
					}

					unlitvert = renderSys.CreateShader(device, asset.raw);
					unlitPipelineInfos.AddShader(unlitvert, asset.raw.descriptor);
				}

				// Unlit frag
				{
					const std::string assetName = "Assets/Shaders/unlit_frag.spha";
					const std::string resName = "/Engine/Resources/Shaders/Forward/unlit.frag";

					ShaderAsset asset;

					if (!asset.Load(assetName))
					{
						if (asset.Import(resName))
						{
							asset.Save(assetName);
						}
					}

					unlitfrag = renderSys.CreateShader(device, asset.raw);
					unlitPipelineInfos.AddShader(unlitfrag, asset.raw.descriptor);
				}
			}




			//// Pipeline
			//{
			//	unlitPipelineInfos.vertexBindingLayout.meshLayout = cubeMesh.GetLayout();
			//	unlitPipeline = renderSys.CreatePipeline(device, unlitPipelineInfos);
			//}


			//// DescSet.
			//{
			//	DescriptorSetCreateInfos infos{ unlitPipeline };
			//	infos.AddBinding<ShaderUBOBinding>(0u, &camUBO, 1);
			//	infos.AddBinding<ShaderUBOBinding>(1u, &modelUBO, 1);
			//	infos.AddBinding<ShaderIBOBinding>(2u, &missText);

			//	cubeDescSet.Create(device, infos);
			//}
		}
	}


	// Loop.
	{
		Chrono chrono;

	#if !SA_CI

		while (!win.ShouldClose())

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

			//	camUBOd.viewInv = camTr.Matrix().GetInversed();
			//	camUBOd.viewPosition = camTr.position;
			//	camUBO.UpdateData(device, &camUBOd, sizeof(camUBOd));
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
			device->WaitIdle();

			/*
			camUBO.Destroy(device);
			modelUBO.Destroy(device);

			cubeDescSet.Destroy(device);
			unlitPipeline.Destroy(device);

			missText.Destroy(device);
			cubeMesh.Destroy(device);

			cmdPool.Destroy(device);
			*/

			renderSys.DestroyShader(device, unlitvert);
			renderSys.DestroyShader(device, unlitfrag);

			surface->DestroyFrameBuffers(device);

			renderSys.DestroyRenderPass(device, renderPass);

			surface->Destroy(device);
			renderSys.DestroyWindowSurface(win, surface);

			renderSys.DestroyDevice(device);

			renderSys.Destroy();
		}


		// Input.
		{
			inputSys.Destroy();
		}


		// Window
		{
			win.Destroy();
			winSys.Destroy();
		}
	}

#if !SA_CI

	std::cin.get();

#endif

	return 0;
}
