// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_VK_RENDER_INTERFACE_GUARD
#define SAPPHIRE_VK_RENDER_INTERFACE_GUARD

#include <SA/Render/Base/ARenderInterface.hpp>

#include <SA/Render/Vulkan/VkInstance.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class RenderInterface : public ARenderInterface
	{
		Instance mInstance;

	public:
		void Create(const AWindowInterface* _winIntf) override final;
		void Destroy() override final;

		ARenderSubInterface* CreateSubInterface(const AGraphicDeviceInfos& _infos) override final;

		ARenderSurface* MakeWindowSurface(AWindow* _win) override final;
		void DestroyWindowSurface(AWindow* _win, ARenderSurface* _surface) override final;

		operator const Instance&() const;
	};
}

#endif

#endif // GUARD
