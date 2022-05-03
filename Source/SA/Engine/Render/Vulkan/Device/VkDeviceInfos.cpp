// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <cstring> // strcmp

#include <Render/Vulkan/Debug/Debug.hpp>

#include <Render/Vulkan/Device/VkDeviceInfos.hpp>
#include <Render/Vulkan/Surface/VkWindowSurface.hpp>

namespace Sa::Vk
{
	DeviceInfos::DeviceInfos(VkPhysicalDevice _device, const QueueRequirements& _reqs) :
		device{ _device },
		reqs{_reqs}
	{
		vkGetPhysicalDeviceProperties(device, &properties);
	}


	uint32_t DeviceInfos::GetID() const noexcept
	{
		return properties.deviceID;
	}
	
	std::string DeviceInfos::GetName() const noexcept
	{
		return properties.deviceName;
	}


//{ Queue Families

	namespace Intl
	{
		void EmplaceFamily(const VkQueueFamilyProperties& _vkFamily,
			DeviceInfos::FamilyInfos& _famInfos,
			uint32_t& _reqNum,
			DeviceInfos::IndexInfos& _currInfos,
			uint32_t _famIndex,
			float _priority)
		{
			const uint32_t num = std::min(_reqNum, _vkFamily.queueCount - _currInfos.num);

			for (uint32_t i = _currInfos.num; i < _currInfos.num + num; ++i)
			{
				_currInfos.queuePriorities.push_back(_priority);
				_famInfos.queueInfos.emplace_back(DeviceInfos::FamilyInfos::QueueInfos{ _famIndex, i });
			}

			_currInfos.num += num;
			_reqNum -= num;
		}
	}

	void DeviceInfos::QueryQueueFamilies(const WindowSurface* _winSurface) noexcept
	{
		SA_ASSERT(Default, SA/Engine/Render/Vulkan, device != VK_NULL_HANDLE, L"Query queue families of a null physical device!");
		SA_ASSERT(Default, SA/Engine/Render/Vulkan, !(reqs.familyFlags.IsSet(QueueFamily::Present) ^ (_winSurface != nullptr)),
			L"QueueType::Present requiere a valid RenderSurface as parameter!");

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		for (uint32_t i = 0; i < queueFamilies.size() && !QueueFamiliesCompleted(); ++i)
			AddFamily(_winSurface, queueFamilies[i], i);
	}

	void DeviceInfos::AddFamily(const WindowSurface* _winSurface, const VkQueueFamilyProperties& _family, uint32_t _famIndex) noexcept
	{
		// TODO: Allow queue with same index but lower device score.

		IndexInfos infos{ _famIndex };

		// Graphics family.
		if (reqs.familyFlags & QueueFamily::Graphics && (_family.queueFlags & VK_QUEUE_GRAPHICS_BIT) && reqs.graphicNum > 0)
			Intl::EmplaceFamily(_family, graphics, reqs.graphicNum, infos, _famIndex, 1.0f);

		// Compute family.
		if (reqs.familyFlags & QueueFamily::Compute && (_family.queueFlags & VK_QUEUE_COMPUTE_BIT) && reqs.computeNum > 0)
			Intl::EmplaceFamily(_family, compute, reqs.computeNum, infos, _famIndex, 1.0f);

		// Present family.
		if (reqs.familyFlags & QueueFamily::Present && reqs.presentNum > 0)
		{
			VkBool32 presentSupport = false;
			SA_VK_ASSERT(vkGetPhysicalDeviceSurfaceSupportKHR(device, _famIndex, *_winSurface, &presentSupport));

			if (presentSupport)
				Intl::EmplaceFamily(_family, present, reqs.presentNum, infos, _famIndex, 0.7f);
		}

		// Transfer family.
		if (reqs.familyFlags & QueueFamily::Transfer && (_family.queueFlags & VK_QUEUE_TRANSFER_BIT) && reqs.transferNum > 0)
				Intl::EmplaceFamily(_family, transfer, reqs.transferNum, infos, _famIndex, 0.5f);

		if (infos.num != 0)
			indexInfos.push_back(infos);
	}

	bool DeviceInfos::QueueFamiliesCompleted() const noexcept
	{
		return reqs.graphicNum == 0 &&
			reqs.computeNum == 0 &&
			reqs.transferNum == 0 &&
			reqs.presentNum == 0;
	}

//}


//{ Extension

	std::vector<const char*> DeviceInfos::GetRequiredExtensions() const
	{
		// Present requiered extensions.
		static constexpr const char* presentRequieredExtensions[] =
		{
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};


		std::vector<const char*> result;

		if (reqs.familyFlags.IsSet(QueueFamily::Present))
			result.insert(result.end(), presentRequieredExtensions, presentRequieredExtensions + sizeof(presentRequieredExtensions)/8);

		return result;
	}

	bool DeviceInfos::CheckExtensionSupport() const noexcept
	{
		uint32_t extensionCount = 0u;
		SA_VK_ASSERT(vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr),
			L"Failed to query physical graphic device extension properties count.");

		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		SA_VK_ASSERT(vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data()),
			L"Failed to query physical graphic device extension properties.");

		std::vector<const char*> requieredExtensions = GetRequiredExtensions();

		// Check each extensions asked are supported.
		for (size_t i = 0; i < requieredExtensions.size(); ++i)
		{
			size_t j = 0;

			for (; j < availableExtensions.size(); ++j)
			{
				// Extension found.
				if (std::strcmp(requieredExtensions[i], availableExtensions[j].extensionName) == 0)
					break;
			}

			// Extension not found.
			if (j == availableExtensions.size())
				return false;
		}

		return true;
	}

//}


	std::vector<VkDeviceQueueCreateInfo> DeviceInfos::GetDeviceCreateInfos() const noexcept
	{
		std::vector<VkDeviceQueueCreateInfo> result;
		result.reserve(indexInfos.size());

		for (auto it = indexInfos.begin(); it != indexInfos.end(); ++it)
		{
			// Create new queue create infos.
			VkDeviceQueueCreateInfo queueInfos{};
			queueInfos.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueInfos.pNext = nullptr;
			queueInfos.flags = 0;
			queueInfos.queueFamilyIndex = it->index;
			queueInfos.queueCount = it->num;
			queueInfos.pQueuePriorities = it->queuePriorities.data();

			result.emplace_back(queueInfos);
		}

		return result;
	}
}
