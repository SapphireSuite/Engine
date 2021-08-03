// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_DEVICE_GUARD
#define SAPPHIRE_RENDER_VK_DEVICE_GUARD

#include <vector>

#include <SA/Config.hpp>

#include <SA/Render/Vulkan/Device/VkGraphicDeviceInfos.hpp>

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
		const VkPhysicalDeviceMemoryProperties& GetMemoryProperties() const noexcept;

		SA_ENGINE_API void Create(const GraphicDeviceInfos& _infos);
		SA_ENGINE_API void Destroy();

		SA_ENGINE_API static std::vector<GraphicDeviceInfos> QuerySuitableDevices(const RenderInstance& _inst, QueueType _reqFamilies, const RenderSurface* _surface = nullptr);
	};
}

#endif

#endif // GUARD
