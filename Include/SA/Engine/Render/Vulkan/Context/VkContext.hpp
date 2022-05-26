// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_CONTEXT_GUARD
#define SAPPHIRE_ENGINE_VK_CONTEXT_GUARD

#include <SA/Engine/Render/Base/Context/ARenderContext.hpp>

#include <SA/Engine/Render/Vulkan/Surface/VkSurface.hpp>
#include <SA/Engine/Render/Vulkan/Pass/VkRenderPass.hpp>
#include <SA/Engine/Render/Vulkan/Context/VkResourceInitializer.hpp>
#include <SA/Engine/Render/Vulkan/Shader/VkShader.hpp>
#include <SA/Engine/Render/Vulkan/Mesh/VkStaticMesh.hpp>
#include <SA/Engine/Render/Vulkan/Texture/VkTexture.hpp>
#include <SA/Engine/Render/Vulkan/Texture/VkCubemap.hpp>
#include <SA/Engine/Render/Vulkan/Pipeline/VkPipelineLayout.hpp>
#include <SA/Engine/Render/Vulkan/Pipeline/VkPipeline.hpp>
#include <SA/Engine/Render/Vulkan/Material/VkMaterial.hpp>

#include <SA/Engine/HI/InterfaceList.hpp>

namespace SA::VK
{
	class Device;

	class Context : public ARenderContext
	{
		Device& mDevice;

		InterfaceList<Surface> mSurfaces;
		InterfaceList<RenderPass> mRenderPasses;
		InterfaceList<ResourceInitializer> mResInits;
		InterfaceList<Shader> mShaders;
		InterfaceList<StaticMesh> mStaticMeshes;
		InterfaceList<Texture> mTextures;
		InterfaceList<Cubemap> mCubemaps;
		InterfaceList<PipelineLayout> mPipelineLayouts;
		InterfaceList<Pipeline> mPipelines;
		InterfaceList<Material> mMaterials;

	public:
		Context(Device& _device) noexcept;

		void Create() override final;
		void Destroy() override final;
		void Clear() override final;


//{ Surface

		ARenderSurface* CreateSurface(AWindowSurface* _winSurface) override final;
		void DestroySurface(ARenderSurface* _surface) override final;

		void CreateFrameBuffers(ARenderSurface* _surface, ARenderPass* _pass, const RenderPassDescriptor& _desc) override final;
		void DestroyFrameBuffers(ARenderSurface* _surface) override final;

		ARenderFrame& BeginSurface(ARenderSurface* _surface) override final;
		void EndSurface(ARenderSurface* _surface) override final;

//}

		ARenderPass* CreateRenderPass(const RenderPassDescriptor& _desc) override final;
		void DestroyRenderPass(ARenderPass* _pass) override final;


//{ Resoures

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


		ARenderPipelineLayout* CreatePipelineLayout(const PipelineLayoutDescriptor& _desc) override final;
		void DestroyPipelineLayout(ARenderPipelineLayout* _pipLayout) override final;

		ARenderPipeline* CreatePipeline(const PipelineDescriptor& _desc, const ARenderPipelineLayout* _pipLayout) override final;
		void DestroyPipeline(ARenderPipeline* _pipeline) override final;


		ARenderMaterial* CreateMaterial(const ARenderPipelineLayout* _pipLayout,
			const PipelineLayoutDescriptor& _pipLayoutDesc,
			const MaterialBindingData& _bindData = MaterialBindingData()) override final;
		void DestroyMaterial(ARenderMaterial* _mat) override final;
		void BindMaterialData(ARenderMaterial* _mat, const MaterialBindingData& _bindData) override final;

//}
	};


	template <typename T>
	struct ContextObjDestroyer
	{
		Device& device;

		void operator()(T& _in)
		{
			_in.Destroy(device);
		}
	};
}


#endif // GUARD
