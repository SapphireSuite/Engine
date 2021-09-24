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
		RenderSurface* const vkSurface = new RenderSurface(_win.CreateVkRenderSurface(mInstance));

		return vkSurface;
	}

	void RenderSystem::DestroyWindowSurface(AWindow& _win, ARenderSurface*& _surface)
	{
		_win.DestroyVkRenderSurface(mInstance, _surface->As<RenderSurface>());

		delete _surface;
		_surface = nullptr;
	}


	RenderSystem::operator const RenderInstance& () const
	{
		return mInstance;
	}
}

#endif
