// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/VkRenderSubInterface.hpp>

#include <SA/Render/Vulkan/Surface/VkWindowSurface.hpp>
#include <SA/Render/Vulkan/Surface/VkSurface.hpp>
#include <SA/Render/Vulkan/Pass/VkRenderPass.hpp>
#include <SA/Render/Vulkan/Pipeline/VkPipeline.hpp>
#include <SA/Render/Vulkan/VkResourceInitializer.hpp>
#include <SA/Render/Vulkan/Shader/VkShader.hpp>
#include <SA/Render/Vulkan/Mesh/VkStaticMesh.hpp>
#include <SA/Render/Vulkan/Texture/VkTexture.hpp>
#include <SA/Render/Vulkan/Texture/VkCubemap.hpp>
#include <SA/Render/Vulkan/Material/VkMaterial.hpp>
#include <SA/Render/Vulkan/Camera/VkCamera.hpp>

namespace Sa::Vk
{
	void RenderSubInterface::Create(const AGraphicDeviceInfos& _infos)
	{
		mDevice.Create(_infos);

		SA_LOG(L"Render Sub-Interface created.", Infos, SA/Render/Vulkan);
	}

	void RenderSubInterface::Destroy()
	{
		mDevice.Destroy();

		SA_LOG(L"Render Sub-Interface destroyed.", Infos, SA/Render/Vulkan);
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
