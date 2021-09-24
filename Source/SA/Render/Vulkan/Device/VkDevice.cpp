// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Device/VkDevice.hpp>

#include <Core/Algorithms/SizeOf.hpp>

#include <Render/Vulkan/Debug/VkValidationLayers.hpp>

#include <Render/Vulkan/VkRenderInstance.hpp>
#include <Render/Vulkan/Device/VkGraphicDeviceInfos.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	std::vector<const char*> GetRequiredExtensions(QueueFamily _reqFamilies)
	{
		// Present requiered extensions.
		static constexpr const char* presentRequieredExtensions[] =
		{
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};


		std::vector<const char*> result;

		if (_reqFamilies & QueueFamily::Present)
			result.insert(result.end(), presentRequieredExtensions, presentRequieredExtensions + SizeOf(presentRequieredExtensions));

		return result;
	}

	bool CheckExtensionSupport(VkPhysicalDevice _device, QueueFamily _reqFamilies)
	{
		uint32 extensionCount = 0u;
		SA_VK_ASSERT(vkEnumerateDeviceExtensionProperties(_device, nullptr, &extensionCount, nullptr),
			L"Failed to query physical graphic device extension properties count.");

		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		SA_VK_ASSERT(vkEnumerateDeviceExtensionProperties(_device, nullptr, &extensionCount, availableExtensions.data()),
			L"Failed to query physical graphic device extension properties.");

		std::vector<const char*> requieredExtensions = GetRequiredExtensions(_reqFamilies);

		// Check each extensions asked are supported.
		for (uint32 i = 0; i < SizeOf(requieredExtensions); ++i)
		{
			bool extensionFound = false;

			for (uint32 j = 0; j < availableExtensions.size(); ++j)
			{
				// Extension found.
				if (strcmp(requieredExtensions[i], availableExtensions[j].extensionName) == 0)
				{
					extensionFound = true;
					break;
				}
			}

			// Extension not found.
			if (!extensionFound)
				return false;
		}

		return true;
	}

	bool IsPhysicalDeviceSuitable(GraphicDeviceInfos& _infos, const RenderSurface* _surface)
	{
		// Check requiered extensions.
		if (!CheckExtensionSupport(_infos.device, _infos.reqs.familyFlags))
			return false;

		// Check queue family suitability.
		_infos.QueryQueueFamilies(_surface);

		if (!_infos.QueueFamiliesCompleted())
			return false;


		//// Graphics SwapChain support.
		////if (_surface && !_surface->CheckSupport(_infos.device))
		////	return false;


		//// TODO: SAVE?
		//// Check properties suitability.
		//VkPhysicalDeviceProperties deviceProperties{};
		//vkGetPhysicalDeviceProperties(_infos.device, &deviceProperties);

		//VkPhysicalDeviceFeatures deviceFeatures{};
		//vkGetPhysicalDeviceFeatures(_infos.device, &deviceFeatures);

		//if (!deviceFeatures.samplerAnisotropy)
		//	return false;

		return true;
	}


	const VkPhysicalDeviceMemoryProperties& Device::GetMemoryProperties() const noexcept
	{
		return mMemProperties;
	}

	void Device::Create(const AGraphicDeviceInfos& _infos)
	{
		const GraphicDeviceInfos& vkInfos = _infos.As<GraphicDeviceInfos>();

		VkPhysicalDeviceFeatures physicalDeviceFeatures{}; // Need braces to ensure C-struct correct initialization.
		//physicalDeviceFeatures.logicOp = VK_TRUE;

		physicalDeviceFeatures.sampleRateShading = VK_TRUE;
		physicalDeviceFeatures.samplerAnisotropy = VK_TRUE;

		//physicalDeviceFeatures.multiViewport = VK_TRUE;

		std::vector<const char*> extensions = GetRequiredExtensions(vkInfos.reqs.familyFlags);
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos = vkInfos.GetDeviceCreateInfos();

		VkDeviceCreateInfo deviceCreateInfo{};
		deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceCreateInfo.pNext = nullptr;
		deviceCreateInfo.flags = 0u;
		deviceCreateInfo.queueCreateInfoCount = static_cast<uint32>(queueCreateInfos.size());
		deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
		deviceCreateInfo.enabledLayerCount = 0u;
		deviceCreateInfo.ppEnabledLayerNames = nullptr;
		deviceCreateInfo.enabledExtensionCount = static_cast<uint32>(extensions.size());
		deviceCreateInfo.ppEnabledExtensionNames = extensions.data();
		deviceCreateInfo.pEnabledFeatures = &physicalDeviceFeatures;

#if SA_VK_VALIDATION_LAYERS

		deviceCreateInfo.enabledLayerCount = ValidationLayers::GetLayerNum();
		deviceCreateInfo.ppEnabledLayerNames = ValidationLayers::GetLayerNames();

#endif

		mPhysicalDevice = vkInfos.device;

		SA_VK_ASSERT(vkCreateDevice(mPhysicalDevice, &deviceCreateInfo, nullptr, &mLogicalDevice),
			L"Failed to create logical device!");

		// Query properties.
		vkGetPhysicalDeviceMemoryProperties(mPhysicalDevice, &mMemProperties);

		queueMgr.Create(*this, vkInfos);

		SA_LOG(L"Graphic device created.", Infos, SA/Render/Vulkan);
	}
	
	void Device::Destroy()
	{
		SA_ASSERT(Default, SA/Render/Vulkan, mLogicalDevice != VK_NULL_HANDLE && mPhysicalDevice != VK_NULL_HANDLE, L"Destroy invalid device.");

		queueMgr.Destroy(*this);

		vkDestroyDevice(mLogicalDevice, nullptr);

		mLogicalDevice = VK_NULL_HANDLE;
		mPhysicalDevice = VK_NULL_HANDLE;

		SA_LOG(L"Graphic device destroyed.", Infos, SA/Render/Vulkan);
	}

	void Device::WaitIdle()
	{
		vkDeviceWaitIdle(mLogicalDevice);
	}


	std::vector<GraphicDeviceInfos> QuerySuitableDevices(const RenderInstance& _inst, const QueueRequirements& _queueReq)
	{
		return Device::QuerySuitableDevices(_inst, nullptr, _queueReq);
	}

	std::vector<GraphicDeviceInfos> Device::QuerySuitableDevices(const RenderInstance& _inst, const RenderSurface* _surface, const QueueRequirements& _queueReq)
	{
		SA_ASSERT(Default, SA/Render/Vulkan, !((bool)(_queueReq.familyFlags & QueueFamily::Present) ^ (_surface != nullptr)),
			L"QueueType::Present requiere a valid RenderSurface as parameter!");

		// Query Physical devices.
		uint32 deviceCount = 0;
		SA_VK_ASSERT(vkEnumeratePhysicalDevices(_inst, &deviceCount, nullptr), L"Failed to query physical graphic device count.");

		SA_ASSERT(Default, SA/Render/Vulkan, deviceCount, L"No GPU with Vulkan support found!");

		std::vector<VkPhysicalDevice> vkDevices(deviceCount);
		SA_VK_ASSERT(vkEnumeratePhysicalDevices(_inst, &deviceCount, vkDevices.data()), L"Failed to enumerate physical graphic devices.");


		std::vector<GraphicDeviceInfos> ghDeviceInfos;
		ghDeviceInfos.reserve(deviceCount);

		for (auto it = vkDevices.begin(); it != vkDevices.end(); ++it)
		{
			GraphicDeviceInfos infos{ *it, _queueReq };

			if (IsPhysicalDeviceSuitable(infos, _surface))
				ghDeviceInfos.emplace_back(infos);
		}

		SA_WARN(!ghDeviceInfos.empty(), SA/Render/Vulkan, L"No suitable graphic device found!");

		// TODO: Implement score: https://vulkan-tutorial.com/Drawing_a_triangle/Setup/Physical_devices_and_queue_families
		//std::sort(ghDeviceInfos.begin(), ghDeviceInfos.end(), AGraphicDeviceInfos::SortScore);

		return ghDeviceInfos;
	}


	Device::operator VkDevice() const noexcept
	{
		return mLogicalDevice;
	}

	Device::operator VkPhysicalDevice() const noexcept
	{
		return mPhysicalDevice;
	}
}

#endif
