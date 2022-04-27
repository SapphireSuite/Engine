// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_RENDER_INTERFACE_GUARD
#define SAPPHIRE_ENGINE_VK_RENDER_INTERFACE_GUARD

#include <SA/Engine/Render/Base/ARenderInterface.hpp>

#include <SA/Engine/Render/Vulkan/VkInstance.hpp>

namespace Sa::Vk
{
    class RenderInterface : public ARenderInterface
    {
		Instance mInstance;

	public:
		void Create(const AWindowInterface* _winIntf = nullptr) override final;
		void Destroy() override final;


#if SA_WINDOW

		// AWindowSurface* CreateWindowSurface(AWindow* _win) override final;
		// void DestroyWindowSurface(AWindow* _win, AWindowSurface* _winSurface) override final;

#endif
    };
}

#endif // GUARD
