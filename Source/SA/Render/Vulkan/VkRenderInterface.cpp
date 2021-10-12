// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/VkRenderInterface.hpp>

#include <Render/Vulkan/Debug/VkValidationLayers.hpp>

#include <Window/Base/AWindow.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	void RenderInterface::Create(const AWindowInterface* _winIntf)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _winIntf, L"Create Render interface with nullptr Window interface!")
		SA_ASSERT(Default, SA/Render/Vulkan, ValidationLayers::CheckValidationSupport(), L"Validation Layers not supported!");

		SA_LOG(L"Render Interface created.", Infos, SA/Render/Vulkan);

		mInstance.Create(_winIntf);
	}

	void RenderInterface::Destroy()
	{
		mInstance.Destroy();

		SA_LOG(L"Render Interface destroyed.", Infos, SA/Render/Vulkan);
	}


	ARenderDevice* RenderInterface::CreateDevice(const AGraphicDeviceInfos& _infos)
	{
		Device* const device = new Device();

		device->Create(_infos.As<GraphicDeviceInfos>());

		SA_LOG(L"Render Device created.", Infos, SA/Render/Vulkan);

		return device;
	}

	void RenderInterface::DestroyDevice(ARenderDevice* _device)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _device);

		_device->Destroy();

		delete _device;

		SA_LOG(L"Render Device destroyed.", Infos, SA/Render/Vulkan);
	}


	ARenderSurface* RenderInterface::MakeWindowSurface(AWindow* _win)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _win);

		Surface* const vkSurface = new Surface(_win->CreateVkRenderSurface(mInstance));

		SA_LOG(L"Window Surface created.", Infos, SA/Render/Vulkan);

		return vkSurface;
	}

	void RenderInterface::DestroyWindowSurface(AWindow* _win, const ARenderDevice* _device, ARenderSurface* _surface)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _win);
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _surface);

		_surface->Destroy(_device);

		SA_LOG(L"Render Surface destroyed.", Infos, SA/Render/Vulkan);

		_win->DestroyVkRenderSurface(mInstance, _surface->As<Surface>());

		SA_LOG(L"Window Surface destroyed.", Infos, SA/Render/Vulkan);

		delete _surface;
	}


	ARenderPass* RenderInterface::CreateRenderPass(const ARenderDevice* _device, const RenderPassDescriptor& _descriptor)
	{
		RenderPass* const pass = new RenderPass();

		pass->Create(_device, _descriptor);

		SA_LOG(L"RenderPass created.", Infos, SA/Render/Vulkan);

		return pass;
	}

	void RenderInterface::DestroyRenderPass(const ARenderDevice* _device, ARenderPass* _pass)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _pass);

		_pass->Destroy(_device);

		delete _pass;

		SA_LOG(L"RenderPass destroyed.", Infos, SA/Render/Vulkan);
	}


	ARenderPipeline* RenderInterface::CreatePipeline(const ARenderDevice* _device, const RenderPipelineDescriptor& _desc)
	{
		Pipeline* const pipeline = new Pipeline();

		pipeline->Create(_device, _desc);

		SA_LOG(L"Render Pipeline created.", Infos, SA/Render/Vulkan);

		return pipeline;
	}

	void RenderInterface::DestroyPipeline(const ARenderDevice* _device, ARenderPipeline* _pipeline)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _pipeline);

		_pipeline->Destroy(_device);

		delete _pipeline;

		SA_LOG(L"Render Pipeline destroyed.", Infos, SA/Render/Vulkan);
	}


//{ Resources

	ARenderResourceInitializer* RenderInterface::CreateResourceInitializer(const ARenderDevice* _device)
	{
		ResourceInitializer* const init = new ResourceInitializer();

		init->Create(_device);

		SA_LOG(L"Render Resource Initializer created.", Infos, SA/Render/Vulkan);

		return init;
	}

	void RenderInterface::DestroyResourceInitializer(ARenderResourceInitializer* _init)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _init);

		_init->Destroy();
		delete _init;

		SA_LOG(L"Render Resource Initializer destroyed.", Infos, SA/Render/Vulkan);
	}


	AShader* RenderInterface::CreateShader(ARenderResourceInitializer* _init, const RawShader& _raw)
	{
		Shader* const shader = new Shader();

		shader->Create(_init, _raw);

		SA_LOG(L"Shader created.", Infos, SA/Render/Vulkan);

		return shader;
	}
	
	void RenderInterface::DestroyShader(const ARenderDevice* _device, AShader* _shader)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _shader);

		_shader->Destroy(_device);

		delete _shader;

		SA_LOG(L"Shader destroyed.", Infos, SA/Render/Vulkan);
	}


	AStaticMesh* RenderInterface::CreateStaticMesh(ARenderResourceInitializer* _init, const RawMesh& _raw)
	{
		StaticMesh* const mesh = new StaticMesh();

		mesh->Create(_init, _raw);

		SA_LOG(L"Mesh created.", Infos, SA/Render/Vulkan);

		return mesh;
	}

	void RenderInterface::DestroyStaticMesh(const ARenderDevice* _device, AStaticMesh* _mesh)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _mesh);

		_mesh->Destroy(_device);

		delete _mesh;

		SA_LOG(L"Mesh destroyed.", Infos, SA/Render/Vulkan);
	}


	ATexture* RenderInterface::CreateTexture(ARenderResourceInitializer* _init, const RawTexture& _raw)
	{
		Texture* const texture = new Texture();

		texture->Create(_init, _raw);

		SA_LOG(L"Texture created.", Infos, SA/Render/Vulkan);

		return texture;
	}

	void RenderInterface::DestroyTexture(const ARenderDevice* _device, ATexture* _texture)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _texture);

		_texture->Destroy(_device);

		delete _texture;

		SA_LOG(L"Texture destroyed.", Infos, SA/Render/Vulkan);
	}

	
	ACubemap* RenderInterface::CreateCubemap(ARenderResourceInitializer* _init, const RawCubemap& _raw)
	{
		Cubemap* const cubemap = new Cubemap();

		cubemap->Create(_init, _raw);

		SA_LOG(L"Cubemap created.", Infos, SA/Render/Vulkan);

		return cubemap;
	}

	void RenderInterface::DestroyCubemap(const ARenderDevice* _device, ACubemap* _cubemap)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _cubemap);

		_cubemap->Destroy(_device);

		delete _cubemap;

		SA_LOG(L"Cubemap destroyed.", Infos, SA/Render/Vulkan);
	}


	ARenderMaterial* RenderInterface::CreateMaterial(const ARenderDevice* _device, const RenderMaterialCreateInfos& _infos)
	{
		Material* const mat = new Material();

		mat->Create(_device, _infos);

		SA_LOG(L"Render Material created.", Infos, SA/Render/Vulkan);

		return mat;
	}

	void RenderInterface::DestroyMaterial(const ARenderDevice* _device, ARenderMaterial* _material)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _material);

		_material->Destroy(_device);

		delete _material;

		SA_LOG(L"Render Material destroyed.", Infos, SA/Render/Vulkan);
	}


	ACamera* RenderInterface::CreateCamera(const ARenderDevice* _device)
	{
		Camera* const camera = new Camera();

		camera->Create(_device);

		SA_LOG(L"Camera created.", Infos, SA/Render/Vulkan);

		return camera;
	}

	void RenderInterface::DestroyCamera(const ARenderDevice* _device, ACamera* _camera)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _camera);

		_camera->Destroy(_device);

		delete _camera;

		SA_LOG(L"Camera destroyed.", Infos, SA/Render/Vulkan);
	}

//}


	RenderInterface::operator const Instance&() const
	{
		return mInstance;
	}
}

#endif
