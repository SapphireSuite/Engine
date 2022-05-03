// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_RENDER_INTERFACE_GUARD
#define SAPPHIRE_ENGINE_VK_RENDER_INTERFACE_GUARD

#include <SA/Engine/Render/Base/ARenderInterface.hpp>

#include <SA/Engine/Render/Vulkan/VkInstance.hpp>
#include <SA/Engine/Render/Vulkan/Device/VkDevice.hpp>
#include <SA/Engine/Render/Vulkan/Surface/VkWindowSurface.hpp>

namespace Sa::Vk
{
    class RenderInterface : public ARenderInterface
    {
		Instance mInstance;

		InterfaceList<WindowSurface> mWindowSurfaces;
		InterfaceList<Device> mDevices;

	public:
		void Create(const AWindowInterface* _winIntf = nullptr) override final;
		void Destroy() override final;
		void Clear() override final;

		PolymorphicVector<ARenderDeviceInfos> QueryDevices(AWindowSurface* _winSurface = nullptr) override final;
		ARenderDevice* CreateDevice(const ARenderDeviceInfos* _infos) override final;
		void DestroyDevice(ARenderDevice* _device) override final;

#if SA_WINDOW

		AWindowSurface* CreateWindowSurface(AWindow* _win) override final;
		void DestroyWindowSurface(AWindowSurface* _winSurface) override final;

#endif
    };
}

#endif // GUARD
