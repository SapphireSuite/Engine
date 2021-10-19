// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_DEVICE_GUARD
#define SAPPHIRE_RENDER_VK_DEVICE_GUARD

#include <vector>

#include <SA/Render/Base/Device/ARenderDevice.hpp>
#include <SA/Render/Vulkan/Device/VkQueueMgr.hpp>

namespace Sa::Vk
{
	class Instance;
	class WindowSurface;

	class Device : public ARenderDevice
	{
		VkDevice mLogicalDevice = VK_NULL_HANDLE;
		VkPhysicalDevice mPhysicalDevice = VK_NULL_HANDLE;

		// Properties.
		VkPhysicalDeviceMemoryProperties mMemProperties;

	public:
		QueueMgr queueMgr;

		const VkPhysicalDeviceMemoryProperties& GetMemoryProperties() const noexcept;

		void Create(const AGraphicDeviceInfos& _infos) override final;
		void Destroy() override final;

		void WaitIdle() override final;


		static std::vector<GraphicDeviceInfos> QuerySuitableDevices(const Instance& _inst,
			const QueueRequirements& _queueReq = QueueRequirements{ QueueFamily::OffScreen });

		static std::vector<GraphicDeviceInfos> QuerySuitableDevices(const Instance& _inst,
			const WindowSurface* _winSurface, const QueueRequirements& _queueReq = QueueRequirements{ QueueFamily::Max });


		operator VkDevice() const noexcept;
		operator VkPhysicalDevice() const noexcept;
	};
}

#endif // GUARD
