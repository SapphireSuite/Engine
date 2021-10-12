// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/VkRenderInterface.hpp>

#include <Render/Vulkan/VkRenderSubInterface.hpp>
#include <Render/Vulkan/Debug/VkValidationLayers.hpp>
#include <Render/Vulkan/Surface/VkWindowSurface.hpp>

#include <Window/Base/AWindow.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	void RenderInterface::Create(const AWindowInterface* _winIntf)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _winIntf, L"Create Render interface with nullptr Window interface!")
		SA_ASSERT(Default, SA/Render/Vulkan, ValidationLayers::CheckValidationSupport(), L"Validation Layers not supported!");


		mInstance.Create(_winIntf);

		SA_LOG(L"Render Interface created.", Infos, SA/Render/Vulkan);
	}

	void RenderInterface::Destroy()
	{
		mInstance.Destroy();

		SA_LOG(L"Render Interface destroyed.", Infos, SA/Render/Vulkan);
	}


	ARenderSubInterface* RenderInterface::CreateSubInterface(const AGraphicDeviceInfos& _infos)
	{
		RenderSubInterface* subIntf = new RenderSubInterface();

		subIntf->Create(_infos);

		return subIntf;
	}


	AWindowSurface* RenderInterface::CreateWindowSurface(AWindow* _win)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _win);

		WindowSurface* const winSurface = new WindowSurface(_win->CreateVkWindowSurface(mInstance));

		return winSurface;
	}

	void RenderInterface::DestroyWindowSurface(AWindow* _win, AWindowSurface* _winSurface)
	{
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _win);
		SA_ASSERT(Nullptr, SA/Render/Vulkan, _winSurface);

		WindowSurface* const vkWinSurface = _winSurface->AsPtr<WindowSurface>();

		_win->DestroyVkWindowSurface(mInstance, *vkWinSurface);

		delete vkWinSurface;
	}


	RenderInterface::operator const Instance&() const
	{
		return mInstance;
	}
}

#endif
