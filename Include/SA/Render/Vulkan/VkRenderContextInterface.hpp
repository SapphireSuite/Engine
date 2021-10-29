// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_RENDER_SUB_INTERFACE_GUARD
#define SAPPHIRE_RENDER_VK_RENDER_SUB_INTERFACE_GUARD

#include <SA/Render/Base/ARenderContextInterface.hpp>

#include <SA/Core/Types/Variadics/SparseVector.hpp>

#include <SA/Render/Vulkan/Surface/VkSurface.hpp>
#include <SA/Render/Vulkan/Pass/VkRenderPass.hpp>
#include <SA/Render/Vulkan/VkResourceInitializer.hpp>
#include <SA/Render/Vulkan/Shader/VkShader.hpp>
#include <SA/Render/Vulkan/Texture/VkTexture.hpp>
#include <SA/Render/Vulkan/Texture/VkCubemap.hpp>

namespace Sa::Vk
{
	class RenderGraphicInterface;

	class RenderContextInterface : public ARenderContextInterface
	{
		const RenderGraphicInterface* mGraphics = nullptr;

		SparseVector<Surface, ARenderSurface> mSurfaces;
		//SparseVector<ResourceInitializer> mResInits;
		SparseVector<RenderPass, ARenderPass> mRenderPasses;
		//SparseVector<Shader> mShaders;
		//SparseVector<Texture> mTextures;
		//SparseVector<Cubemap> mCubemaps;

		const Device& GetDevice() const;

	public:
		void Create(const RenderGraphicInterface* _graphics);
		void Destroy() override final;

		RenderSurfaceHandle CreateSurface(WindowSurfaceHandle _winHandle) override final;
		void DestroySurface(RenderSurfaceHandle& _handle) override final;

		RenderPassHandle CreateRenderPass(const RenderPassDescriptor& _descriptor) override final;
		void DestroyRenderPass(RenderPassHandle& _handle) override final;

		void CreateFrameBuffers(const RenderSurfaceHandle& _surface,
			const RenderPassHandle& _pass,
			const RenderPassDescriptor& _descriptor) override final;
		void DestroyFrameBuffers(const RenderSurfaceHandle& _surface) override final;

		//ARenderPipeline* CreatePipeline(const RenderPipelineDescriptor& _desc) override final;
		//void DestroyPipeline(ARenderPipeline* _pipeline) override final;


//{ Resources
	
		//RenderResourceInitializerHandle CreateResourceInitializer() override final;
		//void DestroyResourceInitializer(RenderResourceInitializerHandle& _init) override final;
		//void SubmitResourceInitializer(const RenderResourceInitializerHandle& _init) override final;

		//ShaderHandle CreateShader(const RenderResourceInitializerHandle& _init, const RawShader& _raw) override final;
		//void DestroyShader(ShaderHandle& _shader) override final;

		//AStaticMesh* CreateStaticMesh(ARenderResourceInitializer* _init, const RawMesh& _raw) override final;
		//void DestroyStaticMesh(AStaticMesh* _mesh) override final;

		//TextureHandle CreateTexture(const RenderResourceInitializerHandle& _init, const RawTexture& _raw) override final;
		//void DestroyTexture(TextureHandle& _texture) override final;

		//CubemapHandle CreateCubemap(const RenderResourceInitializerHandle& _init, const RawCubemap& _raw) override final;
		//void DestroyCubemap(CubemapHandle& _cubemap) override final;


		//ARenderMaterial* CreateMaterial(const RenderMaterialCreateInfos& _infos) override final;
		//void DestroyMaterial(ARenderMaterial* _material) override final;

		//ACamera* CreateCamera() override final;
		//void DestroyCamera(ACamera* _camera) override final;
//}
	};
}

#endif // GUARD
