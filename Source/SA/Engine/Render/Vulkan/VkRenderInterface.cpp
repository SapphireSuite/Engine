// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/VkRenderInterface.hpp>

#include <HI/Cast.hpp>

#include <Render/Vulkan/Debug/VkValidationLayers.hpp>

#include <Render/Vulkan/Device/VkDeviceInfos.hpp>

#if SA_WINDOW

	#include <Window/Base/AWindow.hpp>

#endif

namespace Sa::Vk
{
	void RenderInterface::Create(const AWindowInterface* _winIntf)
	{
		ARenderInterface::Create(_winIntf);

		// _winIntf can be nullptr for offscreen rendering.
		SA_ASSERT(Default, SA/Render/Vulkan, ValidationLayers::CheckValidationSupport(), L"Validation Layers not supported!");

		mInstance.Create(_winIntf);

		SA_LOG(L"Render Interface created.", Infos, SA/Render/Vulkan);
	}

	void RenderInterface::Destroy()
	{
		ARenderInterface::Destroy();

		mInstance.Destroy();

		SA_LOG(L"Render Interface destroyed.", Infos, SA/Render/Vulkan);
	}

	void RenderInterface::Clear()
	{
		ARenderInterface::Clear();

		mWindowSurfaces.Clear(WindowSurfaceDestroyer{ mInstance });
		
		mDevices.Clear();

		SA_LOG(L"Render Interface cleared.", Infos, SA/Render/Vulkan);
	}


	std::vector<ARenderDeviceInfos*> RenderInterface::QueryDevices(AWindowSurface* _winSurface)
	{
		CheckCreated();
	
		return std::vector<ARenderDeviceInfos*>();
	}
	
	ARenderDevice* RenderInterface::CreateDevice(ARenderDeviceInfos* _infos)
	{
		CheckCreated();
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _infos);

		Device* const device = mDevices.Emplace();

		device->Create(CastRef<Vk::DeviceInfos>(_infos));

		return device;
	}
	
	void RenderInterface::DestroyDevice(ARenderDevice* _device)
	{
		CheckCreated();
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _device);

		mDevices.Erase(_device, DestroyFunctor<Device>());
	}


#if SA_WINDOW

	AWindowSurface* RenderInterface::CreateWindowSurface(AWindow* _win)
	{
		CheckCreated();
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _win);

		WindowSurface* winSurface = mWindowSurfaces.Emplace();

		winSurface->Create(_win, mInstance);

		return winSurface;
	}

	void RenderInterface::DestroyWindowSurface(AWindowSurface* _winSurface)
	{
		CheckCreated();
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _winSurface);

		bool bRemoved = mWindowSurfaces.Erase(_winSurface, WindowSurfaceDestroyer{ mInstance });

		if(!bRemoved)
			SA_LOG(L"Window Surface [" << _winSurface << "] not created with this inferface.", Error, SA/Engine/Render/Vulkan);
	}

#endif
}
