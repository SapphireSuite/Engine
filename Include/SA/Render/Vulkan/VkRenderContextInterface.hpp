// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_RENDER_SUB_INTERFACE_GUARD
#define SAPPHIRE_RENDER_VK_RENDER_SUB_INTERFACE_GUARD

#include <forward_list>

#include <SA/Render/Base/ARenderContextInterface.hpp>

#include <SA/Render/Vulkan/Surface/VkSurface.hpp>
#include <SA/Render/Vulkan/Pass/VkRenderPass.hpp>
#include <SA/Render/Vulkan/VkResourceInitializer.hpp>
#include <SA/Render/Vulkan/Shader/VkShader.hpp>
#include <SA/Render/Vulkan/Mesh/VkBLStaticMesh.hpp>
#include <SA/Render/Vulkan/Texture/VkTexture.hpp>
#include <SA/Render/Vulkan/Texture/VkCubemap.hpp>

#include <SA/Render/Vulkan/Buffers/GPU/VkGPUBufferHeap.hpp>

namespace Sa::Vk
{
	class RenderGraphicInterface;

	class RenderContextInterface : public ARenderContextInterface
	{
		const RenderGraphicInterface* mGraphics = nullptr;

		std::forward_list<Surface> mSurfaces;
		std::forward_list<RenderPass> mRenderPasses;
		std::forward_list<ResourceInitializer> mResInits;
		std::forward_list<Shader> mShaders;
		std::forward_list<BLStaticMesh> mStaticMeshes;
		std::forward_list<Texture> mTextures;
		std::forward_list<Cubemap> mCubemaps;

		GPUBufferHeap mMeshVertexHeap;
		GPUBufferHeap mMeshIndicesHeap;


		const Device& GetDevice() const;

		template <typename ResT>
		void EraseResource(std::vector<ResT*>& _vec, ResT* _res);

		template <typename ResT, typename DestroyerT>
		void DestroyResources(std::forward_list<ResT>& _list, DestroyerT _destroyer);

	public:
		void Create(const RenderGraphicInterface* _graphics);
		void Destroy() override final;

		ARenderSurface* CreateSurface(AWindowSurface* _winSurface) override final;
		void DestroySurface(ARenderSurface* _surface) override final;

		ARenderPass* CreateRenderPass(const RenderPassDescriptor& _descriptor) override final;
		void DestroyRenderPass(ARenderPass* _pass) override final;

		void CreateFrameBuffers(ARenderSurface* _surface, ARenderPass* _pass, const RenderPassDescriptor& _descriptor) override final;
		void DestroyFrameBuffers(ARenderSurface* _surface) override final;

		//ARenderPipeline* CreatePipeline(const RenderPipelineDescriptor& _desc) override final;
		//void DestroyPipeline(ARenderPipeline* _pipeline) override final;


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


		//ARenderMaterial* CreateMaterial(const RenderMaterialCreateInfos& _infos) override final;
		//void DestroyMaterial(ARenderMaterial* _material) override final;

		//ACamera* CreateCamera() override final;
		//void DestroyCamera(ACamera* _camera) override final;
//}
	};
}

#endif // GUARD
