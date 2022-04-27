// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/VkRenderInterface.hpp>

#include <Render/Vulkan/Debug/VkValidationLayers.hpp>


// #include <Core/Algorithms/Cast.hpp>

// #include <Render/Vulkan/VkRenderGraphicInterface.hpp>
// #include <Render/Vulkan/Surface/VkWindowSurface.hpp>

#if SA_WINDOW

	// #include <Window/Base/AWindow.hpp>

#endif

namespace Sa::Vk
{
	void RenderInterface::Create(const AWindowInterface* _winIntf)
	{
		// _winIntf can be nullptr for offscreen rendering.
		SA_ASSERT(Default, SA/Render/Vulkan, ValidationLayers::CheckValidationSupport(), L"Validation Layers not supported!");

		mInstance.Create(_winIntf);

		SA_LOG(L"Render Interface created.", Infos, SA/Render/Vulkan);
	}

	void RenderInterface::Destroy()
	{
		mInstance.Destroy();

		SA_LOG(L"Render Interface destroyed.", Infos, SA/Render/Vulkan);
	}


	// ARenderGraphicInterface* RenderInterface::CreateGraphicInterface(const AGraphicDeviceInfos& _infos)
	// {
	// 	RenderGraphicInterface* graphics = new RenderGraphicInterface();

	// 	graphics->Create(_infos);

	// 	return graphics;
	// }


#if SA_WINDOW

	// AWindowSurface* RenderInterface::CreateWindowSurface(AWindow* _win)
	// {
	// 	SA_ASSERT(Nullptr, SA/Render/Vulkan, _win);

	// 	WindowSurface* const winSurface = new WindowSurface(_win->CreateVkWindowSurface(mInstance));

	// 	return winSurface;
	// }

	// void RenderInterface::DestroyWindowSurface(AWindow* _win, AWindowSurface* _winSurface)
	// {
	// 	SA_ASSERT(Nullptr, SA/Render/Vulkan, _win);
	// 	SA_ASSERT(Nullptr, SA/Render/Vulkan, _winSurface);

	// 	WindowSurface* const vkWinSurface = Cast<WindowSurface>(_winSurface);

	// 	_win->DestroyVkWindowSurface(mInstance, *vkWinSurface);

	// 	delete vkWinSurface;
	// }

#endif
}
