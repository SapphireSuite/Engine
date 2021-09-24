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
		Device* device = new Device();

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

	void RenderSystem::DestroyWindowSurface(AWindow& _win, ARenderSurface*& _surface)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _surface);

		_win.DestroyVkRenderSurface(mInstance, _surface->As<Surface>());

		delete _surface;
		_surface = nullptr;
	}


	ARenderPass* RenderSystem::CreateRenderPass(ARenderDevice* _device, const RenderPassDescriptor& _descriptor)
	{
		SA_ASSERT(Nullptr, SA / Render / Vulkan, _device);

		RenderPass* const pass = new RenderPass();

		pass->Create(*_device, _descriptor);

		return pass;
	}

	void RenderSystem::DestroyRenderPass(ARenderDevice* _device, ARenderPass* _pass)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _device);
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _pass);

		_pass->Destroy(*_device);

		delete _pass;
	}


	RenderSystem::operator const Instance& () const
	{
		return mInstance;
	}
}

#endif
