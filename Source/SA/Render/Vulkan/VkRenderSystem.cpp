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

		return device;
	}

	void RenderSystem::DestroyDevice(ARenderDevice* _device)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _device);

		_device->Destroy();

		delete _device;
	}


	ARenderSurface* RenderSystem::CreateWindowSurface(AWindow& _win)
	{
		Surface* const vkSurface = new Surface(_win.CreateVkRenderSurface(mInstance));

		return vkSurface;
	}

	void RenderSystem::DestroyWindowSurface(AWindow& _win, ARenderSurface* _surface)
	{
		_win.DestroyVkRenderSurface(mInstance, _surface->As<Surface>());

		delete _surface;
	}


	ARenderPass* RenderSystem::CreateRenderPass(ARenderDevice* _device, const RenderPassDescriptor& _descriptor)
	{
		RenderPass* const pass = new RenderPass();

		pass->Create(_device, _descriptor);

		return pass;
	}

	void RenderSystem::DestroyRenderPass(ARenderDevice* _device, ARenderPass* _pass)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _pass);

		_pass->Destroy(_device);

		delete _pass;
	}


	ARenderPipeline* RenderSystem::CreatePipeline(ARenderDevice* _device, const RenderPipelineCreateInfos& _infos)
	{
		Pipeline* const pipeline = new Pipeline();

		pipeline->Create(_device, _infos);

		return pipeline;
	}

	void RenderSystem::DestroyPipeline(ARenderDevice* _device, ARenderPipeline* _pipeline)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _pipeline);

		_pipeline->Destroy(_device);

		delete _pipeline;
	}


	ARenderResourceInitializer* RenderSystem::CreateResourceInitializer(ARenderDevice* _device)
	{
		ResourceInitializer* const context = new ResourceInitializer();

		context->Create(_device);

		return context;
	}

	void RenderSystem::DestroyResourceInitializer(ARenderResourceInitializer* _init)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _init);

		_init->Destroy();
		delete _init;
	}


	AShader* RenderSystem::CreateShader(ARenderResourceInitializer* _init, const RawShader& _raw)
	{
		Shader* const shader = new Shader();

		shader->Create(_init, _raw);

		return shader;
	}
	
	void RenderSystem::DestroyShader(ARenderDevice* _device, AShader* _shader)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _shader);

		_shader->Destroy(_device);

		delete _shader;
	}


	ATexture* RenderSystem::CreateTexture(ARenderResourceInitializer* _init, const RawTexture& _raw)
	{
		Texture* const texture = new Texture();

		texture->Create(_init, _raw);

		return texture;
	}

	void RenderSystem::DestroyTexture(ARenderDevice* _device, ATexture* _texture)
	{
		_texture->Destroy(_device);

		delete _texture;
	}

	
	ACubemap* RenderSystem::CreateCubemap(ARenderResourceInitializer* _init, const RawCubemap& _raw)
	{
		Cubemap* const cubemap = new Cubemap();

		cubemap->Create(_init, _raw);

		return cubemap;
	}

	void RenderSystem::DestroyCubemap(ARenderDevice* _device, ACubemap* _cubemap)
	{
		_cubemap->Destroy(_device);

		delete _cubemap;
	}


	RenderSystem::operator const Instance& () const
	{
		return mInstance;
	}
}

#endif
