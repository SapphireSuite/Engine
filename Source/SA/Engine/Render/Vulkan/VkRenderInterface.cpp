// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/VkRenderInterface.hpp>

#include <HI/Cast.hpp>

#include <Render/Vulkan/Debug/VkValidationLayers.hpp>

#include <Render/Vulkan/Device/VkDeviceInfos.hpp>

#if SA_WINDOW

	#include <Window/Base/AWindow.hpp>

#endif

namespace SA::VK
{
	void RenderInterface::Create(const AWindowInterface* _winIntf)
	{
		ARenderInterface::Create(_winIntf);

		// _winIntf can be nullptr for offscreen rendering.
		SA_ASSERT(Default, SA/Engine/Render/Vulkan, ValidationLayers::CheckValidationSupport(), L"Validation Layers not supported!");

		mInstance.Create(_winIntf);

		SA_LOG(L"Render Interface created.", Infos, SA/Engine/Render/Vulkan);
	}

	void RenderInterface::Destroy()
	{
		ARenderInterface::Destroy();

		mInstance.Destroy();

		SA_LOG(L"Render Interface destroyed.", Infos, SA/Engine/Render/Vulkan);
	}

	void RenderInterface::Clear()
	{
		ARenderInterface::Clear();

		mDevices.Clear(DestroyFunctor<Device>());
		
		mWindowSurfaces.Clear(WindowSurfaceDestroyer{ mInstance });

		SA_LOG(L"Render Interface cleared.", Infos, SA/Engine/Render/Vulkan);
	}


	PolymorphicVector<ARenderDeviceInfos> RenderInterface::QueryDevices(AWindowSurface* _winSurface)
	{
		CheckCreated();
	
		std::vector<DeviceInfos> deviceInfos;

		if(_winSurface)
		{
			WindowSurface* const vkWinSurface = Cast<WindowSurface>(_winSurface);
			SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, vkWinSurface, L"Window surface not of type VK::WindowSurface.");

			deviceInfos = Device::QuerySuitableDevices(mInstance, vkWinSurface);
		}
		else
			deviceInfos = Device::QuerySuitableDevices(mInstance);

		return deviceInfos;
	}
	
	ARenderDevice* RenderInterface::CreateDevice(const ARenderDeviceInfos* _infos)
	{
		CheckCreated();
		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, _infos);

		Device* const device = mDevices.Emplace();

		device->Create(CastRef<VK::DeviceInfos>(_infos));

		return device;
	}
	
	void RenderInterface::DestroyDevice(ARenderDevice* _device)
	{
		CheckCreated();
		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, _device);

		mDevices.Erase(_device, DestroyFunctor<Device>());
	}


#if SA_WINDOW

	AWindowSurface* RenderInterface::CreateWindowSurface(AWindow* _win)
	{
		CheckCreated();
		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, _win);

		WindowSurface* winSurface = mWindowSurfaces.Emplace();

		winSurface->Create(_win, mInstance);

		return winSurface;
	}

	void RenderInterface::DestroyWindowSurface(AWindowSurface* _winSurface)
	{
		CheckCreated();
		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, _winSurface);

		bool bRemoved = mWindowSurfaces.Erase(_winSurface, WindowSurfaceDestroyer{ mInstance });

		if(!bRemoved)
			SA_LOG(L"Window Surface [" << _winSurface << "] not created with this inferface.", Error, SA/Engine/Render/Vulkan);
	}

#endif
}
