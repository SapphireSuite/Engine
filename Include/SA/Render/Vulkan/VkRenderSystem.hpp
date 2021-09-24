// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_VK_RENDER_SYSTEM_GUARD
#define SAPPHIRE_VK_RENDER_SYSTEM_GUARD

#include <SA/Render/Base/ARenderSystem.hpp>

#include <SA/Render/Vulkan/VkInstance.hpp>
#include <SA/Render/Vulkan/Device/VkDevice.hpp>
#include <SA/Render/Vulkan/Surface/VkSurface.hpp>
#include <SA/Render/Vulkan/Pass/VkRenderPass.hpp>
#include <SA/Render/Vulkan/Pipeline/VkPipeline.hpp>
#include <SA/Render/Vulkan/VkResourceInitializer.hpp>
#include <SA/Render/Vulkan/Shader/VkShader.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class RenderSystem : public ARenderSystem
	{
		Instance mInstance;

	public:
		void Create(const AWindowSystem& _winSys) override final;
		void Destroy() override final;

		ARenderDevice* CreateDevice(const AGraphicDeviceInfos& _infos) override final;
		void DestroyDevice(ARenderDevice* _device) override final;

		ARenderSurface* CreateWindowSurface(AWindow& _win) override final;
		void DestroyWindowSurface(AWindow& _win, ARenderSurface* _surface) override final;

		ARenderPass* CreateRenderPass(ARenderDevice* _device, const RenderPassDescriptor& _descriptor) override final;
		void DestroyRenderPass(ARenderDevice* _device, ARenderPass* _pass) override final;

		ARenderPipeline* CreatePipeline(ARenderDevice* _device, const RenderPipelineCreateInfos& _infos) override final;
		void DestroyPipeline(ARenderDevice* _device, ARenderPipeline* _pipeline) override final;

		ARenderResourceInitializer* CreateResourceInitializer(ARenderDevice* _device) override final;
		void DestroyResourceInitializer(ARenderResourceInitializer* _init) override final;

		AShader* CreateShader(ARenderResourceInitializer* _init, const RawShader& _raw) override final;
		void DestroyShader(ARenderDevice* _device, AShader* _shader) override final;


		operator const Instance& () const;
	};
}

#endif

#endif // GUARD
