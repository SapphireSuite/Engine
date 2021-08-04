// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_DEVICE_GUARD
#define SAPPHIRE_RENDER_VK_DEVICE_GUARD

#include <vector>

#include <SA/Config.hpp>

#include <SA/Render/Vulkan/Device/VkQueueMgr.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class RenderInstance;
	class RenderSurface;

	class Device
	{
		VkDevice mLogicalDevice = VK_NULL_HANDLE;
		VkPhysicalDevice mPhysicalDevice = VK_NULL_HANDLE;

		// Properties.
		VkPhysicalDeviceMemoryProperties mMemProperties;

	public:
		QueueMgr queueMgr;

		const VkPhysicalDeviceMemoryProperties& GetMemoryProperties() const noexcept;

		SA_ENGINE_API void Create(const GraphicDeviceInfos& _infos);
		SA_ENGINE_API void Destroy();

		SA_ENGINE_API static std::vector<GraphicDeviceInfos> QuerySuitableDevices(const RenderInstance& _inst,
			const QueueRequirements& _queueReq = QueueRequirements{ QueueFamily::OffScreen });

		SA_ENGINE_API static std::vector<GraphicDeviceInfos> QuerySuitableDevices(const RenderInstance& _inst,
			const RenderSurface* _surface, const QueueRequirements& _queueReq = QueueRequirements{ QueueFamily::Max });


		operator VkDevice() const noexcept;
		operator VkPhysicalDevice() const noexcept;
	};
}

#endif

#endif // GUARD
