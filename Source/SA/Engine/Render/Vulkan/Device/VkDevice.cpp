// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Debug/Debug.hpp>

#include <Render/Vulkan/VkInstance.hpp>

#include <Render/Vulkan/Device/VkDevice.hpp>
#include <Render/Vulkan/Device/VkDeviceInfos.hpp>

namespace Sa::Vk
{
	const VkPhysicalDeviceMemoryProperties& Device::GetMemoryProperties() const noexcept
	{
		return mMemProperties;
	}


	void Device::Create(const DeviceInfos& _infos)
	{
		ARenderDevice::Create();
		
		VkPhysicalDeviceFeatures physicalDeviceFeatures{}; // Need braces to ensure C-struct correct initialization.
		//physicalDeviceFeatures.logicOp = VK_TRUE;

		physicalDeviceFeatures.sampleRateShading = VK_TRUE;
		physicalDeviceFeatures.samplerAnisotropy = VK_TRUE;

		//physicalDeviceFeatures.multiViewport = VK_TRUE;

		std::vector<const char*> extensions = _infos.GetRequiredExtensions();
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos = _infos.GetDeviceCreateInfos();

		VkDeviceCreateInfo deviceCreateInfo{};
		deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceCreateInfo.pNext = nullptr;
		deviceCreateInfo.flags = 0u;
		deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
		deviceCreateInfo.enabledLayerCount = 0u;
		deviceCreateInfo.ppEnabledLayerNames = nullptr;
		deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		deviceCreateInfo.ppEnabledExtensionNames = extensions.data();
		deviceCreateInfo.pEnabledFeatures = &physicalDeviceFeatures;

#if SA_VK_VALIDATION_LAYERS

		deviceCreateInfo.enabledLayerCount = ValidationLayers::GetLayerNum();
		deviceCreateInfo.ppEnabledLayerNames = ValidationLayers::GetLayerNames();

#endif

		mPhysicalDevice = _infos.device;

		SA_VK_ASSERT(vkCreateDevice(mPhysicalDevice, &deviceCreateInfo, nullptr, &mLogicalDevice),
			L"Failed to create logical device!");

		// Query properties.
		vkGetPhysicalDeviceMemoryProperties(mPhysicalDevice, &mMemProperties);


		SA_LOG(L"Render Device [" << _infos.GetName() << ":\t" << _infos.GetID() << L"] created.", Infos, SA/Engine/Render/Vulkan);
	}

	void Device::Destroy()
	{
		ARenderDevice::Destroy();

		WaitIdle();

		vkDestroyDevice(mLogicalDevice, nullptr);

		mLogicalDevice = VK_NULL_HANDLE;
		mPhysicalDevice = VK_NULL_HANDLE;

		SA_LOG(L"Render Device destroyed.", Infos, SA/Engine/Render/Vulkan);
	}

	void Device::Clear()
	{
		ARenderDevice::Clear();

		WaitIdle();
		
		mContexts.Clear(DestroyFunctor<Context>());

		SA_LOG(L"Render Device cleared.", Infos, SA/Engine/Render/Vulkan);
	}


	void Device::WaitIdle() const
	{
		vkDeviceWaitIdle(mLogicalDevice);
	}


	ARenderContext* Device::CreateRenderContext()
	{
		CheckCreated();

		Context* const context = mContexts.Emplace();

		context->Create(*this);

		return context;
	}
	
	void Device::DestroyRenderContext(ARenderContext* _context)
	{
		CheckCreated();
		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, _context);

		WaitIdle();

		mContexts.Erase(_context, DestroyFunctor<Context>());
	}


//{ Query Devices



	bool IsPhysicalDeviceSuitable(DeviceInfos& _infos, const WindowSurface* _winSurface)
	{
		// Check requiered extensions.
		if (!_infos.CheckExtensionSupport())
			return false;

		// Check queue family suitability.
		_infos.QueryQueueFamilies(_winSurface);

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

	std::vector<DeviceInfos> Device::QuerySuitableDevices(const Instance& _inst, const QueueRequirements& _queueReq)
	{
		return Device::QuerySuitableDevices(_inst, nullptr, _queueReq);
	}

	std::vector<DeviceInfos> Device::QuerySuitableDevices(const Instance& _inst,
		const WindowSurface* _winSurface,
		const QueueRequirements& _queueReq)
	{
		// Query Physical devices.
		uint32_t deviceCount = 0;
		SA_VK_ASSERT(vkEnumeratePhysicalDevices(_inst, &deviceCount, nullptr), L"Failed to query physical graphic device count.");

		SA_ASSERT(Default, SA/Engine/Render/Vulkan, deviceCount, L"No GPU with Vulkan support found!");

		std::vector<VkPhysicalDevice> vkDevices(deviceCount);
		SA_VK_ASSERT(vkEnumeratePhysicalDevices(_inst, &deviceCount, vkDevices.data()), L"Failed to enumerate physical graphic devices.");

		
		std::vector<DeviceInfos> deviceInfos;
		deviceInfos.reserve(deviceCount);

		for (auto it = vkDevices.begin(); it != vkDevices.end(); ++it)
		{
			DeviceInfos infos{ *it, _queueReq };

			if (IsPhysicalDeviceSuitable(infos, _winSurface))
				deviceInfos.emplace_back(infos);
		}

		SA_WARN(!deviceInfos.empty(), SA/Engine/Render/Vulkan, L"No suitable graphic device found!");

		// TODO: Implement score: https://vulkan-tutorial.com/Drawing_a_triangle/Setup/Physical_devices_and_queue_families
		//std::sort(deviceInfos.begin(), deviceInfos.end(), ARenderDeviceInfos::SortScore);

		return deviceInfos;
	}

//}

	
	Device::operator VkDevice() const noexcept
	{
		return mLogicalDevice;
	}
	
	Device::operator VkPhysicalDevice() const noexcept
	{
		return mPhysicalDevice;
	}
}
