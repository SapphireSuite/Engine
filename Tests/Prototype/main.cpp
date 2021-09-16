// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <iostream>

#include <SA/Collections/Debug>
using namespace Sa;

#include <SA/Window/GLFW/GLFWWindow.hpp>
#include <SA/Window/GLFW/GLFWWindowSystem.hpp>

#include <SA/Input/GLFW/GLFWInputSystem.hpp>
#include <SA/Input/Base/Key/Bindings/InputKeyAction.hpp>
#include <SA/Input/Base/Key/Bindings/InputKeyRange.hpp>
#include <SA/Input/Base/Axis/Bindings/InputAxisAction.hpp>
#include <SA/Input/Base/Axis/Bindings/InputAxisRange.hpp>

#include <SA/Render/Vulkan/VkRenderSystem.hpp>
#include <SA/Render/Vulkan/VkRenderInstance.hpp>
#include <SA/Render/Vulkan/Surface/VkRenderSurface.hpp>
#include <SA/Render/Vulkan/Device/VkDevice.hpp>
#include <SA/Render/Vulkan/Device/VkCommandPool.hpp>
#include <SA/Render/Vulkan/Pass/VkRenderPass.hpp>
#include <SA/Render/Vulkan/Buffers/VkFrameBuffer.hpp>
#include <SA/Render/Vulkan/Buffers/VkCommandBuffer.hpp>
#include <SA/Render/Vulkan/Mesh/VkStaticMesh.hpp>
#include <SA/Render/Vulkan/Shader/VkShader.hpp>
#include <SA/Render/Vulkan/Pipeline/VkPipeline.hpp>
#include <SA/Render/Vulkan/Material/VkMaterial.hpp>
#include <SA/Render/Vulkan/Buffers/VkBuffer.hpp>

#include <SA/Render/Base/Material/Bindings/MaterialUBOBinding.hpp>
#include <SA/Render/Base/Material/Bindings/MaterialIBOBinding.hpp>

#include <SA/SDK/Assets/ModelAsset.hpp>
#include <SA/SDK/Assets/ShaderAsset.hpp>

GLFW::WindowSystem winSys;
GLFW::Window win;

GLFW::InputSystem inputSys;

Vk::RenderSystem renderSys;
Vk::RenderInstance renderInst;
Vk::Device device;
Vk::RenderSurface surface;
RenderPassDescriptor renderPassDesc;
Vk::RenderPass renderPass;
Vk::CommandPool cmdPool;
std::vector<Vk::CommandBuffer> cmdBuffers;
uint32 imageIndex = 0u;

Vk::StaticMesh cubeMesh;
Vk::Shader unlitvert;
Vk::Shader unlitfrag;
Vk::Pipeline unlitPipeline;
Vk::Material cubeMat;
Vk::Buffer camUBO;
Vk::Buffer modelUBO;

const Vec2ui winDim{ 1200u, 800u };

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

			//inputContext->axis.Bind<InputAxisRange>(Axis::MouseX, [](float _inX) { SA_LOG("MouseX: " << _inX); });
			//inputContext->axis.Bind<InputAxisRange>(Axis::MouseY, [](float _inY) { SA_LOG("MouseY: " << _inY); });
		}


		// Render
		{
			renderSys.Create();
			renderInst.Create(winSys);
			surface = win.CreateVkRenderSurface(renderInst);
			
			std::vector<Vk::GraphicDeviceInfos> deviceInfos = Vk::Device::QuerySuitableDevices(renderInst, &surface);
			device.Create(deviceInfos[0]);

			surface.Create(device);


			renderPassDesc = RenderPassDescriptor::DefaultSingle(&surface);
			renderPassDesc.subPassDescs[0].sampling = SampleBits::Sample1Bit;

			renderPass.Create(device, renderPassDesc);

			surface.CreateFrameBuffers(device, renderPass, renderPassDesc);

			cmdPool.Create(device, device.queueMgr.graphics.GetQueue(0).GetFamilyIndex());

			for(uint32 i = 0; i < 3; ++i)
				cmdBuffers.push_back(cmdPool.Allocate(device, VK_COMMAND_BUFFER_LEVEL_PRIMARY));
		}

		// Assets
		{
			// CUBE.
			constexpr char* cubeMeshAssetName = "Assets/Meshes/cube.spha";
			const std::string cubeMeshResName = "../../../../Resources/Meshes/cube.obj";

			MeshAsset cubeMeshAsset;
			if (!cubeMeshAsset.Load(cubeMeshAssetName))
			{
				ModelAsset cubeAsset;
				if (cubeAsset.Import(cubeMeshResName))
				{
					cubeAsset.meshes[0].Save(cubeMeshAssetName);
					cubeMeshAsset = std::move(cubeAsset.meshes[0]);
				}
			}


			// Submit
			ResourceHolder resHolder;
			cmdBuffers[0].Begin();

			cubeMesh.Create(device, cmdBuffers[0], resHolder, cubeMeshAsset.rawData);

			cmdBuffers[0].End();

			VkCommandBuffer bbb = cmdBuffers[0];

			// Submit commands.
			VkSubmitInfo submitInfo{};
			submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submitInfo.pNext = nullptr;
			submitInfo.waitSemaphoreCount = 0u;
			submitInfo.pWaitSemaphores = nullptr;
			submitInfo.pWaitDstStageMask = nullptr;
			submitInfo.commandBufferCount = 1u;
			submitInfo.pCommandBuffers = &bbb;
			submitInfo.signalSemaphoreCount = 0u;
			submitInfo.pSignalSemaphores = nullptr;

			vkQueueSubmit(device.queueMgr.transfer.GetQueue(0), 1, &submitInfo, VK_NULL_HANDLE);
			vkQueueWaitIdle(device.queueMgr.transfer.GetQueue(0));

			resHolder.FreeAll();


			// Shaders
			{
				// Unlit vert
				{
					constexpr char* assetName = "Assets/Shaders/unlit_vert.spha";
					const std::string resName = "../../../../Resources/Shaders/Forward/unlit.vert";

					ShaderAsset asset;

					if(!asset.Load(assetName))
					{
						if (asset.Import(resName))
						{
							asset.Save(assetName);
						}
					}

					unlitvert.Create(device, asset.rawData);
				}

				// Unlit frag
				{
					constexpr char* assetName = "Assets/Shaders/unlit_frag.spha";
					const std::string resName = "../../../../Resources/Shaders/Forward/unlit.frag";

					ShaderAsset asset;

					if (!asset.Load(assetName))
					{
						if (asset.Import(resName))
						{
							asset.Save(assetName);
						}
					}

					unlitfrag.Create(device, asset.rawData);
				}
			}


			// Pipeline
			{
				PipelineCreateInfos infos{ renderPass, renderPassDesc };
				infos.vertexBindingLayout = VertexBindingLayout{ VertexLayout::Make<VertexComp::PTex>(), cubeMesh.GetLayout() };
				infos.shaders = { { &unlitvert, ShaderStage::Vertex }, { &unlitfrag, ShaderStage::Fragment } };
				infos.bindings = {
					{ 0u, ShaderStage::Vertex, ShaderBindingType::UniformBuffer },
					{ 1u, ShaderStage::Vertex, ShaderBindingType::UniformBuffer },
					{ 2u, ShaderStage::Fragment, ShaderBindingType::ImageSampler2D }
				};

				unlitPipeline.Create(device, infos);
			}


			// Material.
			{
				MaterialCreateInfos infos{ unlitPipeline };
				//infos.AddBinding<MaterialUBOBinding>(0u, &camUBO);
				//infos.AddBinding<MaterialUBOBinding>(1u, &modelUBO);

				cubeMat.Create(device, infos);
			}
		}
	}


	// Loop.
	{
	#if !SA_CI

		while (!win.ShouldClose())

	#endif
		{
			inputSys.Update();

			Vk::FrameBuffer& frameBuffer = surface.Begin(device);

			Vk::CommandBuffer& cmdBuffer = cmdBuffers[imageIndex];

			cmdBuffer.Begin();

			frameBuffer.Begin(cmdBuffer);
			frameBuffer.End(cmdBuffer);

			cmdBuffer.End();

			surface.End(device, { cmdBuffer });

			imageIndex = (imageIndex + 1) % 3;
		}
	}


	// Uninit
	{
		// Render
		{
			vkDeviceWaitIdle(device);

			cubeMat.Destroy(device);
			unlitPipeline.Destroy(device);

			unlitvert.Destroy(device);
			unlitfrag.Destroy(device);

			cubeMesh.Destroy(device);

			cmdPool.Destroy(device);

			surface.DestroyFrameBuffers(device);

			renderPass.Destroy(device);
			surface.Destroy(renderInst, device);

			device.Destroy();

			renderInst.Destroy();
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