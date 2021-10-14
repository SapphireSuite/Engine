// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_RENDER_SUB_INTERFACE_GUARD
#define SAPPHIRE_RENDER_VK_RENDER_SUB_INTERFACE_GUARD

#include <SA/Render/Base/ARenderSubInterface.hpp>

#include <SA/Render/Vulkan/Device/VkDevice.hpp>

namespace Sa::Vk
{
	class RenderSubInterface : public ARenderSubInterface
	{
		Device mDevice;
		
		VkDescriptorSetLayout mCameraDescSetLayout;
		VkDescriptorSetLayout mModelDescSetLayout;

		void CreateCameraDescriptorSetLayout();
		void DestroyCameraDescriptorSetLayout();

		void CreateModelDescriptorSetLayout();
		void DestroyModelDescriptorSetLayout();

	public:
		void Create(const AGraphicDeviceInfos& _infos) override final;
		void Destroy() override final;

		ARenderSurface* CreateSurface(AWindowSurface* _winSurface) override final;
		void DestroySurface(ARenderSurface* _surface) override final;

		ARenderPass* CreateRenderPass(const RenderPassDescriptor& _descriptor) override final;
		void DestroyRenderPass(ARenderPass* _pass) override final;

		void CreateFrameBuffers(ARenderSurface* _surface, ARenderPass* _pass, const RenderPassDescriptor& _descriptor) override final;
		void DestroyFrameBuffers(ARenderSurface* _surface) override final;

		ARenderPipeline* CreatePipeline(const RenderPipelineDescriptor& _desc) override final;
		void DestroyPipeline(ARenderPipeline* _pipeline) override final;


//{ Resources
	
		ARenderResourceInitializer* CreateResourceInitializer() override final;
		void DestroyResourceInitializer(ARenderResourceInitializer* _init) override final;
		void SubmitResourceInitializer(ARenderResourceInitializer* _init) override final;

		AShader* CreateShader(ARenderResourceInitializer* _init, const RawShader& _raw) override final;
		void DestroyShader(AShader* _shader) override final;

		AStaticMesh* CreateStaticMesh(ARenderResourceInitializer* _init, const RawMesh& _raw) override final;
		void DestroyStaticMesh(AStaticMesh* _mesh) override final;

		ATexture* CreateTexture(ARenderResourceInitializer* _init, const RawTexture& _raw) override final;
		void DestroyTexture(ATexture* _texture) override final;

		ACubemap* CreateCubemap(ARenderResourceInitializer* _init, const RawCubemap& _raw) override final;
		void DestroyCubemap(ACubemap* _cubemap) override final;


		ARenderMaterial* CreateMaterial(const RenderMaterialCreateInfos& _infos) override final;
		void DestroyMaterial(ARenderMaterial* _material) override final;

		ACamera* CreateCamera() override final;
		void DestroyCamera(ACamera* _camera) override final;
//}
	};
}

#endif // GUARD
