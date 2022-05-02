// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_DEVICE_GUARD
#define SAPPHIRE_ENGINE_VK_DEVICE_GUARD

#include <SA/Support/API/Vulkan.hpp>

#include <SA/Engine/Render/Base/Device/ARenderDevice.hpp>

#include <SA/Engine/Render/Vulkan/Device/VkContext.hpp>

namespace Sa::Vk
{
	class DeviceInfos;

	class Device : public ARenderDevice
	{
		VkDevice mLogicalDevice = VK_NULL_HANDLE;
		VkPhysicalDevice mPhysicalDevice = VK_NULL_HANDLE;

		/// Properties.
		VkPhysicalDeviceMemoryProperties mMemProperties;

		InterfaceList<Context> mContexts;


        using ARenderDevice::Create; // overloaded.

	public:
		void Create(const DeviceInfos& _infos);
		void Destroy() override final;
		void Clear() override final;

		void WaitIdle() const override final;

		ARenderContext* CreateRenderContext() override final;
		void DestroyRenderContext(ARenderContext* _context) override final;
	};
}

#endif // GUARD
