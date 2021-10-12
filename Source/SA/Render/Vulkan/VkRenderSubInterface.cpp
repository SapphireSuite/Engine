// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/VkRenderSubInterface.hpp>

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

	
	void RenderSubInterface::CreateSurface(ARenderSurface* _surface)
	{
		_surface->Create(&mDevice);
	}

	void RenderSubInterface::DestroySurface(ARenderSurface* _surface)
	{
		_surface->Destroy(&mDevice);
	}


	ARenderPass* RenderSubInterface::CreateRenderPass(const RenderPassDescriptor& _descriptor)
	{
		RenderPass* const pass = new RenderPass();

		pass->Create(&mDevice, _descriptor);

		return pass;
	}
	
	void RenderSubInterface::DestroyRenderPass(ARenderPass* _pass)
	{
		_pass->Destroy(&mDevice);

		delete _pass;
	}


	ARenderPipeline* RenderSubInterface::CreatePipeline(const RenderPipelineDescriptor& _desc)
	{
		Pipeline* const pipeline = new Pipeline();

		pipeline->Create(&mDevice, _desc);

		return pipeline;
	}

	void RenderSubInterface::DestroyPipeline(ARenderPipeline* _pipeline)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _pipeline);

		_pipeline->Destroy(&mDevice);

		delete _pipeline;
	}


//{ Resources

	ARenderResourceInitializer* RenderSubInterface::CreateResourceInitializer()
	{
		ResourceInitializer* const init = new ResourceInitializer();

		init->Create(&mDevice);

		return init;
	}

	void RenderSubInterface::DestroyResourceInitializer(ARenderResourceInitializer* _init)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _init);

		_init->Destroy();
		delete _init;
	}


	AShader* RenderSubInterface::CreateShader(ARenderResourceInitializer* _init, const RawShader& _raw)
	{
		Shader* const shader = new Shader();

		shader->Create(_init, _raw);

		return shader;
	}

	void RenderSubInterface::DestroyShader(AShader* _shader)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _shader);

		_shader->Destroy(&mDevice);

		delete _shader;
	}

	
	AStaticMesh* RenderSubInterface::CreateStaticMesh(ARenderResourceInitializer* _init, const RawMesh& _raw)
	{
		StaticMesh* const mesh = new StaticMesh();

		mesh->Create(_init, _raw);

		return mesh;
	}
	
	void RenderSubInterface::DestroyStaticMesh(AStaticMesh* _mesh)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _mesh);

		_mesh->Destroy(&mDevice);

		delete _mesh;
	}

	
	ATexture* RenderSubInterface::CreateTexture(ARenderResourceInitializer* _init, const RawTexture& _raw)
	{
		Texture* const texture = new Texture();

		texture->Create(_init, _raw);

		return texture;
	}
	
	void RenderSubInterface::DestroyTexture(ATexture* _texture)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _texture);

		_texture->Destroy(&mDevice);

		delete _texture;
	}

	
	ACubemap* RenderSubInterface::CreateCubemap(ARenderResourceInitializer* _init, const RawCubemap& _raw)
	{
		Cubemap* const cubemap = new Cubemap();

		cubemap->Create(_init, _raw);

		return cubemap;
	}
	
	void RenderSubInterface::DestroyCubemap(ACubemap* _cubemap)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _cubemap);

		_cubemap->Destroy(&mDevice);

		delete _cubemap;
	}


	
	ARenderMaterial* RenderSubInterface::CreateMaterial(const RenderMaterialCreateInfos& _infos)
	{
		Material* const mat = new Material();

		mat->Create(&mDevice, _infos);

		return mat;
	}
	
	void RenderSubInterface::DestroyMaterial(ARenderMaterial* _material)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _material);

		_material->Destroy(&mDevice);

		delete _material;
	}

	
	ACamera* RenderSubInterface::CreateCamera()
	{
		Camera* const camera = new Camera();

		camera->Create(&mDevice);

		return camera;
	}
	
	void RenderSubInterface::DestroyCamera(ACamera* _camera)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _camera);

		_camera->Destroy(&mDevice);

		delete _camera;
	}

//}
}
