// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/VkRenderSubInterface.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>

#include <Render/Vulkan/Surface/VkWindowSurface.hpp>
#include <Render/Vulkan/Surface/VkSurface.hpp>
#include <Render/Vulkan/Pass/VkRenderPass.hpp>
#include <Render/Vulkan/Pipeline/VkPipeline.hpp>
#include <Render/Vulkan/VkResourceInitializer.hpp>
#include <Render/Vulkan/Shader/VkShader.hpp>
#include <Render/Vulkan/Mesh/VkStaticMesh.hpp>
#include <Render/Vulkan/Texture/VkTexture.hpp>
#include <Render/Vulkan/Texture/VkCubemap.hpp>
#include <Render/Vulkan/Material/VkMaterial.hpp>
#include <Render/Vulkan/Camera/VkCamera.hpp>

namespace Sa::Vk
{
	void RenderSubInterface::Create(const AGraphicDeviceInfos& _infos)
	{
		mDevice.Create(_infos);

		CreateCameraDescriptorSetLayout();
		CreateModelDescriptorSetLayout();

		SA_LOG(L"Render Sub-Interface created.", Infos, SA/Render/Vulkan);
	}

	void RenderSubInterface::Destroy()
	{
		DestroyModelDescriptorSetLayout();
		DestroyCameraDescriptorSetLayout();

		mDevice.Destroy();

		SA_LOG(L"Render Sub-Interface destroyed.", Infos, SA/Render/Vulkan);
	}


	void RenderSubInterface::CreateCameraDescriptorSetLayout()
	{
		constexpr uint32 size = 1u;
		VkDescriptorSetLayoutBinding descSetLayout[size]{};


		// Camera UBO
		descSetLayout[0].binding = 0;
		descSetLayout[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descSetLayout[0].descriptorCount = 1;
		descSetLayout[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
		descSetLayout[0].pImmutableSamplers = nullptr;



		VkDescriptorSetLayoutCreateInfo descriptorSetLayoutInfo{};
		descriptorSetLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		descriptorSetLayoutInfo.pNext = nullptr;
		descriptorSetLayoutInfo.flags = 0u;
		descriptorSetLayoutInfo.bindingCount = size;
		descriptorSetLayoutInfo.pBindings = descSetLayout;

		SA_VK_ASSERT(vkCreateDescriptorSetLayout(mDevice, &descriptorSetLayoutInfo, nullptr, &mCameraDescSetLayout),
			L"Failed to create camera descriptor set layout!");
	}

	void RenderSubInterface::DestroyCameraDescriptorSetLayout()
	{
		vkDestroyDescriptorSetLayout(mDevice, mCameraDescSetLayout, nullptr);
	}


	void RenderSubInterface::CreateModelDescriptorSetLayout()
	{
		constexpr uint32 size = 1u;
		VkDescriptorSetLayoutBinding descSetLayout[size]{};


		// Model UBO
		descSetLayout[0].binding = 0;
		descSetLayout[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descSetLayout[0].descriptorCount = 1;
		descSetLayout[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
		descSetLayout[0].pImmutableSamplers = nullptr;



		VkDescriptorSetLayoutCreateInfo descriptorSetLayoutInfo{};
		descriptorSetLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		descriptorSetLayoutInfo.pNext = nullptr;
		descriptorSetLayoutInfo.flags = 0u;
		descriptorSetLayoutInfo.bindingCount = size;
		descriptorSetLayoutInfo.pBindings = descSetLayout;

		SA_VK_ASSERT(vkCreateDescriptorSetLayout(mDevice, &descriptorSetLayoutInfo, nullptr, &mModelDescSetLayout),
			L"Failed to create model descriptor set layout!");
	}

	void RenderSubInterface::DestroyModelDescriptorSetLayout()
	{
		vkDestroyDescriptorSetLayout(mDevice, mModelDescSetLayout, nullptr);
	}

	
	ARenderSurface* RenderSubInterface::CreateSurface(AWindowSurface* _winSurface)
	{
		Surface* const surface = new Surface();

		surface->Create(mDevice, _winSurface->As<WindowSurface>());

		return surface;
	}

	void RenderSubInterface::DestroySurface(ARenderSurface* _surface)
	{
		Surface* const vkSurface = _surface->AsPtr<Surface>();

		vkSurface->Destroy(mDevice);

		delete vkSurface;
	}


	ARenderPass* RenderSubInterface::CreateRenderPass(const RenderPassDescriptor& _descriptor)
	{
		RenderPass* const pass = new RenderPass();

		pass->Create(mDevice, _descriptor);

		return pass;
	}
	
	void RenderSubInterface::DestroyRenderPass(ARenderPass* _pass)
	{
		RenderPass* const vkPass = _pass->AsPtr<RenderPass>();

		vkPass->Destroy(mDevice);

		delete vkPass;
	}


	void RenderSubInterface::CreateFrameBuffers(ARenderSurface* _surface, ARenderPass* _pass, const RenderPassDescriptor& _descriptor)
	{
		_surface->As<Surface>().CreateFrameBuffers(mDevice, _pass->As<RenderPass>(), _descriptor);
	}

	void RenderSubInterface::DestroyFrameBuffers(ARenderSurface* _surface)
	{
		_surface->As<Surface>().DestroyFrameBuffers(mDevice);
	}


	ARenderPipeline* RenderSubInterface::CreatePipeline(const RenderPipelineDescriptor& _desc)
	{
		Pipeline* const pipeline = new Pipeline();

		pipeline->Create(mDevice, _desc);

		return pipeline;
	}

	void RenderSubInterface::DestroyPipeline(ARenderPipeline* _pipeline)
	{
		Pipeline* const vkPipeline = _pipeline->AsPtr<Pipeline>();

		vkPipeline->Destroy(mDevice);

		delete vkPipeline;
	}


//{ Resources

	ARenderResourceInitializer* RenderSubInterface::CreateResourceInitializer()
	{
		ResourceInitializer* const init = new ResourceInitializer();

		init->Create(mDevice);

		return init;
	}

	void RenderSubInterface::DestroyResourceInitializer(ARenderResourceInitializer* _init)
	{
		ResourceInitializer* const vkInit = _init->AsPtr<ResourceInitializer>();

		vkInit->Destroy(mDevice);

		delete vkInit;
	}

	void RenderSubInterface::SubmitResourceInitializer(ARenderResourceInitializer* _init)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _init);

		_init->As<ResourceInitializer>().Submit(mDevice);
	}


	AShader* RenderSubInterface::CreateShader(ARenderResourceInitializer* _init, const RawShader& _raw)
	{
		Shader* const shader = new Shader();

		shader->Create(mDevice, _init->As<ResourceInitializer>(), _raw);

		return shader;
	}

	void RenderSubInterface::DestroyShader(AShader* _shader)
	{
		Shader* const vkShader = _shader->AsPtr<Shader>();

		vkShader->Destroy(mDevice);

		delete vkShader;
	}

	
	AStaticMesh* RenderSubInterface::CreateStaticMesh(ARenderResourceInitializer* _init, const RawMesh& _raw)
	{
		StaticMesh* const mesh = new StaticMesh();

		mesh->Create(mDevice, _init->As<ResourceInitializer>(), _raw);

		return mesh;
	}
	
	void RenderSubInterface::DestroyStaticMesh(AStaticMesh* _mesh)
	{
		StaticMesh* const vkMesh = _mesh->AsPtr<StaticMesh>();

		vkMesh->Destroy(mDevice);

		delete vkMesh;
	}

	
	ATexture* RenderSubInterface::CreateTexture(ARenderResourceInitializer* _init, const RawTexture& _raw)
	{
		Texture* const texture = new Texture();

		texture->Create(mDevice, _init->As<ResourceInitializer>(), _raw);

		return texture;
	}
	
	void RenderSubInterface::DestroyTexture(ATexture* _texture)
	{
		Texture* const vkTexture = _texture->AsPtr<Texture>();

		vkTexture->Destroy(mDevice);

		delete vkTexture;
	}

	
	ACubemap* RenderSubInterface::CreateCubemap(ARenderResourceInitializer* _init, const RawCubemap& _raw)
	{
		Cubemap* const cubemap = new Cubemap();

		cubemap->Create(mDevice, _init->As<ResourceInitializer>(), _raw);

		return cubemap;
	}
	
	void RenderSubInterface::DestroyCubemap(ACubemap* _cubemap)
	{
		Cubemap* const vkCubemap = _cubemap->AsPtr<Cubemap>();

		vkCubemap->Destroy(mDevice);

		delete vkCubemap;
	}

	
	ARenderMaterial* RenderSubInterface::CreateMaterial(const RenderMaterialCreateInfos& _infos)
	{
		Material* const mat = new Material();

		mat->Create(mDevice, _infos);

		return mat;
	}
	
	void RenderSubInterface::DestroyMaterial(ARenderMaterial* _material)
	{
		Material* const vkMat = _material->AsPtr<Material>();

		vkMat->Destroy(mDevice);

		delete vkMat;
	}

	
	ACamera* RenderSubInterface::CreateCamera()
	{
		Camera* const camera = new Camera();

		camera->Create(mDevice);

		return camera;
	}
	
	void RenderSubInterface::DestroyCamera(ACamera* _camera)
	{
		Camera* const vkCamera = _camera->AsPtr<Camera>();

		vkCamera->Destroy(mDevice);

		delete vkCamera;
	}

//}
}
