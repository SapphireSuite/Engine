// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/VkRenderInterface.hpp>
// #include <Render/Vulkan/VkRenderGraphicInterface.hpp>

#include <Render/Vulkan/Debug/VkValidationLayers.hpp>

#include <Render/Vulkan/Surface/VkWindowSurface.hpp>

#if SA_WINDOW

	#include <Window/Base/AWindow.hpp>

#endif

namespace Sa::Vk
{
	void RenderInterface::Create(const AWindowInterface* _winIntf)
	{
		HardwareInterface::Create();

		// _winIntf can be nullptr for offscreen rendering.
		SA_ASSERT(Default, SA/Render/Vulkan, ValidationLayers::CheckValidationSupport(), L"Validation Layers not supported!");

		mInstance.Create(_winIntf);

		SA_LOG(L"Render Interface created.", Infos, SA/Render/Vulkan);
	}

	void RenderInterface::Destroy()
	{
		HardwareInterface::Destroy();

		mInstance.Destroy();

		SA_LOG(L"Render Interface destroyed.", Infos, SA/Render/Vulkan);
	}

	void RenderInterface::Clear()
	{
		mWindowSurfaces.Clear(WindowSurfaceDestroyer{ mInstance });
	}


	// ARenderGraphicInterface* RenderInterface::CreateGraphicInterface(const AGraphicDeviceInfos& _infos)
	// {
	// 	RenderGraphicInterface* graphics = new RenderGraphicInterface();

	// 	graphics->Create(_infos);

	// 	return graphics;
	// }


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
