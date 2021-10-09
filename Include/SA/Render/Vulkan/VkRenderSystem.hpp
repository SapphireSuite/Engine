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
#include <SA/Render/Vulkan/Mesh/VkStaticMesh.hpp>
#include <SA/Render/Vulkan/Texture/VkTexture.hpp>
#include <SA/Render/Vulkan/Texture/VkCubemap.hpp>
#include <SA/Render/Vulkan/Material/VkMaterial.hpp>

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

		ARenderSurface* MakeWindowSurface(AWindow& _win) override final;
		void DestroyWindowSurface(AWindow& _win, const ARenderDevice* _device, ARenderSurface* _surface) override final;

		ARenderPass* CreateRenderPass(const ARenderDevice* _device, const RenderPassDescriptor& _descriptor) override final;
		void DestroyRenderPass(const ARenderDevice* _device, ARenderPass* _pass) override final;

		ARenderPipeline* CreatePipeline(const ARenderDevice* _device, const RenderPipelineCreateInfos& _infos) override final;
		void DestroyPipeline(const ARenderDevice* _device, ARenderPipeline* _pipeline) override final;


//{ Resources

		ARenderResourceInitializer* CreateResourceInitializer(const ARenderDevice* _device) override final;
		void DestroyResourceInitializer(ARenderResourceInitializer* _init) override final;

		AShader* CreateShader(ARenderResourceInitializer* _init, const RawShader& _raw) override final;
		void DestroyShader(const ARenderDevice* _device, AShader* _shader) override final;

		AStaticMesh* CreateStaticMesh(ARenderResourceInitializer* _init, const RawMesh& _raw) override final;
		void DestroyStaticMesh(const ARenderDevice* _device, AStaticMesh* _mesh) override final;

		ATexture* CreateTexture(ARenderResourceInitializer* _init, const RawTexture& _raw) override final;
		void DestroyTexture(const ARenderDevice* _device, ATexture* _texture) override final;

		ACubemap* CreateCubemap(ARenderResourceInitializer* _init, const RawCubemap& _raw) override final;
		void DestroyCubemap(const ARenderDevice* _device, ACubemap* _cubemap) override final;


		ARenderMaterial* CreateMaterial(const ARenderDevice* _device,
			const ARenderPipeline* _pipeline,
			const RenderPipelineCreateInfos& _infos,
			uint32 setIndex = 0) override final;
		void DestroyMaterial(const ARenderDevice* _device, ARenderMaterial* _material) override final;

//}

		operator const Instance& () const;
	};
}

#endif

#endif // GUARD
