// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/VkRenderSystem.hpp>

#include <Render/Vulkan/Debug/VkValidationLayers.hpp>

#include <Window/Base/AWindow.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	void RenderSystem::Create(const AWindowSystem& _winSys)
	{
		SA_ASSERT(Default, SA/Render/Vulkan, ValidationLayers::CheckValidationSupport(), L"Validation Layers not supported!");

		SA_LOG(L"Render System created.", Infos, SA/Render/Vulkan);

		mInstance.Create(_winSys);
	}

	void RenderSystem::Destroy()
	{
		mInstance.Destroy();

		SA_LOG(L"Render System destroyed.", Infos, SA/Render/Vulkan);
	}


	ARenderDevice* RenderSystem::CreateDevice(const AGraphicDeviceInfos& _infos)
	{
		Device* const device = new Device();

		device->Create(_infos.As<GraphicDeviceInfos>());

		SA_LOG(L"Render Device created.", Infos, SA/Render/Vulkan);

		return device;
	}

	void RenderSystem::DestroyDevice(ARenderDevice* _device)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _device);

		_device->Destroy();

		delete _device;

		SA_LOG(L"Render Device destroyed.", Infos, SA/Render/Vulkan);
	}


	ARenderSurface* RenderSystem::MakeWindowSurface(AWindow* _win)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _win);

		Surface* const vkSurface = new Surface(_win->CreateVkRenderSurface(mInstance));

		SA_LOG(L"Window Surface created.", Infos, SA/Render/Vulkan);

		return vkSurface;
	}

	void RenderSystem::DestroyWindowSurface(AWindow* _win, const ARenderDevice* _device, ARenderSurface* _surface)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _win);
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _surface);

		_surface->Destroy(_device);

		SA_LOG(L"Render Surface destroyed.", Infos, SA/Render/Vulkan);

		_win->DestroyVkRenderSurface(mInstance, _surface->As<Surface>());

		SA_LOG(L"Window Surface destroyed.", Infos, SA/Render/Vulkan);

		delete _surface;
	}


	ARenderPass* RenderSystem::CreateRenderPass(const ARenderDevice* _device, const RenderPassDescriptor& _descriptor)
	{
		RenderPass* const pass = new RenderPass();

		pass->Create(_device, _descriptor);

		SA_LOG(L"RenderPass created.", Infos, SA/Render/Vulkan);

		return pass;
	}

	void RenderSystem::DestroyRenderPass(const ARenderDevice* _device, ARenderPass* _pass)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _pass);

		_pass->Destroy(_device);

		delete _pass;

		SA_LOG(L"RenderPass destroyed.", Infos, SA/Render/Vulkan);
	}


	ARenderPipeline* RenderSystem::CreatePipeline(const ARenderDevice* _device, const RenderPipelineDescriptor& _desc)
	{
		Pipeline* const pipeline = new Pipeline();

		pipeline->Create(_device, _desc);

		SA_LOG(L"Render Pipeline created.", Infos, SA/Render/Vulkan);

		return pipeline;
	}

	void RenderSystem::DestroyPipeline(const ARenderDevice* _device, ARenderPipeline* _pipeline)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _pipeline);

		_pipeline->Destroy(_device);

		delete _pipeline;

		SA_LOG(L"Render Pipeline destroyed.", Infos, SA/Render/Vulkan);
	}


//{ Resources

	ARenderResourceInitializer* RenderSystem::CreateResourceInitializer(const ARenderDevice* _device)
	{
		ResourceInitializer* const init = new ResourceInitializer();

		init->Create(_device);

		SA_LOG(L"Render Resource Initializer created.", Infos, SA/Render/Vulkan);

		return init;
	}

	void RenderSystem::DestroyResourceInitializer(ARenderResourceInitializer* _init)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _init);

		_init->Destroy();
		delete _init;

		SA_LOG(L"Render Resource Initializer destroyed.", Infos, SA/Render/Vulkan);
	}


	AShader* RenderSystem::CreateShader(ARenderResourceInitializer* _init, const RawShader& _raw)
	{
		Shader* const shader = new Shader();

		shader->Create(_init, _raw);

		SA_LOG(L"Shader created.", Infos, SA/Render/Vulkan);

		return shader;
	}
	
	void RenderSystem::DestroyShader(const ARenderDevice* _device, AShader* _shader)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _shader);

		_shader->Destroy(_device);

		delete _shader;

		SA_LOG(L"Shader destroyed.", Infos, SA/Render/Vulkan);
	}


	AStaticMesh* RenderSystem::CreateStaticMesh(ARenderResourceInitializer* _init, const RawMesh& _raw)
	{
		StaticMesh* const mesh = new StaticMesh();

		mesh->Create(_init, _raw);

		SA_LOG(L"Mesh created.", Infos, SA/Render/Vulkan);

		return mesh;
	}

	void RenderSystem::DestroyStaticMesh(const ARenderDevice* _device, AStaticMesh* _mesh)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _mesh);

		_mesh->Destroy(_device);

		delete _mesh;

		SA_LOG(L"Mesh destroyed.", Infos, SA/Render/Vulkan);
	}


	ATexture* RenderSystem::CreateTexture(ARenderResourceInitializer* _init, const RawTexture& _raw)
	{
		Texture* const texture = new Texture();

		texture->Create(_init, _raw);

		SA_LOG(L"Texture created.", Infos, SA/Render/Vulkan);

		return texture;
	}

	void RenderSystem::DestroyTexture(const ARenderDevice* _device, ATexture* _texture)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _texture);

		_texture->Destroy(_device);

		delete _texture;

		SA_LOG(L"Texture destroyed.", Infos, SA/Render/Vulkan);
	}

	
	ACubemap* RenderSystem::CreateCubemap(ARenderResourceInitializer* _init, const RawCubemap& _raw)
	{
		Cubemap* const cubemap = new Cubemap();

		cubemap->Create(_init, _raw);

		SA_LOG(L"Cubemap created.", Infos, SA/Render/Vulkan);

		return cubemap;
	}

	void RenderSystem::DestroyCubemap(const ARenderDevice* _device, ACubemap* _cubemap)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _cubemap);

		_cubemap->Destroy(_device);

		delete _cubemap;

		SA_LOG(L"Cubemap destroyed.", Infos, SA/Render/Vulkan);
	}


	ARenderMaterial* RenderSystem::CreateMaterial(const ARenderDevice* _device, const RenderMaterialCreateInfos& _infos)
	{
		Material* const mat = new Material();

		mat->Create(_device, _infos);

		SA_LOG(L"Render Material created.", Infos, SA/Render/Vulkan);

		return mat;
	}

	void RenderSystem::DestroyMaterial(const ARenderDevice* _device, ARenderMaterial* _material)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _material);

		_material->Destroy(_device);

		delete _material;

		SA_LOG(L"Render Material destroyed.", Infos, SA/Render/Vulkan);
	}


	ACamera* RenderSystem::CreateCamera(const ARenderDevice* _device)
	{
		Camera* const camera = new Camera();

		camera->Create(_device);

		SA_LOG(L"Camera created.", Infos, SA/Render/Vulkan);

		return camera;
	}

	void RenderSystem::DestroyCamera(const ARenderDevice* _device, ACamera* _camera)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _camera);

		_camera->Destroy(_device);

		delete _camera;

		SA_LOG(L"Camera destroyed.", Infos, SA/Render/Vulkan);
	}

//}


	RenderSystem::operator const Instance&() const
	{
		return mInstance;
	}
}

#endif
