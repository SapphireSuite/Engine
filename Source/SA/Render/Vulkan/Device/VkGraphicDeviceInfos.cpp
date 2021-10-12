// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Device/VkGraphicDeviceInfos.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Surface/VkWindowSurface.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	GraphicDeviceInfos::GraphicDeviceInfos(VkPhysicalDevice _device, const QueueRequirements& _reqs) noexcept :
		device{ _device },
		reqs{ _reqs }
	{
		VkPhysicalDeviceProperties properties;
		vkGetPhysicalDeviceProperties(device, &properties);

		ID = properties.deviceID;
		name = properties.deviceName;

		// TODO: Use this.
		(void)properties.limits.maxViewports;
		(void)properties.limits.maxSamplerAnisotropy;
	}

	void GraphicDeviceInfos::QueryQueueFamilies(const WindowSurface* _winSurface) noexcept
	{
		SA_ASSERT(Default, SA/Render/Vulkan, device != VK_NULL_HANDLE, L"Query queue families of a null physical device!");

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		for (uint32 i = 0; i < queueFamilies.size() && !QueueFamiliesCompleted(); ++i)
			AddFamily(_winSurface, queueFamilies[i], i);
	}

	void GraphicDeviceInfos::AddFamily(const WindowSurface* _winSurface, const VkQueueFamilyProperties& _family, uint32 _famIndex) noexcept
	{
		// TODO: Allow queue with same index but lower device score.

		IndexInfos infos{ _famIndex };

		// Graphics family.
		if (reqs.familyFlags & QueueFamily::Graphics && (_family.queueFlags & VK_QUEUE_GRAPHICS_BIT) && reqs.graphicNum > 0)
		{
			const uint32 num = std::min(reqs.graphicNum, _family.queueCount - infos.num);

			for (uint32 i = infos.num; i < infos.num + num; ++i)
				graphics.queueInfos.emplace_back(FamilyInfos::QueueInfos{ _famIndex, i });

			infos.num += num;
			reqs.graphicNum -= num;
		}

		// Compute family.
		if (reqs.familyFlags & QueueFamily::Compute && (_family.queueFlags & VK_QUEUE_COMPUTE_BIT) && reqs.computeNum > 0)
		{
			const uint32 num = std::min(reqs.computeNum, _family.queueCount - infos.num);

			for (uint32 i = infos.num; i < infos.num + num; ++i)
				compute.queueInfos.emplace_back(FamilyInfos::QueueInfos{ _famIndex, i });

			infos.num += num;
			reqs.computeNum -= num;
		}

		// Present family.
		if (reqs.familyFlags & QueueFamily::Present && reqs.presentNum > 0)
		{
			VkBool32 presentSupport = false;
			SA_VK_ASSERT(vkGetPhysicalDeviceSurfaceSupportKHR(device, _famIndex, *_winSurface, &presentSupport));

			if (presentSupport)
			{
				const uint32 num = std::min(reqs.presentNum, _family.queueCount - infos.num);

				for (uint32 i = infos.num; i < infos.num + num; ++i)
					present.queueInfos.emplace_back(FamilyInfos::QueueInfos{ _famIndex, i });

				infos.num += num;
				reqs.presentNum -= num;
			}
		}

		// Transfer family.
		if (reqs.familyFlags & QueueFamily::Transfer && (_family.queueFlags & VK_QUEUE_TRANSFER_BIT) && reqs.transferNum > 0)
		{
			const uint32 num = std::min(reqs.transferNum, _family.queueCount - infos.num);

			for (uint32 i = infos.num; i < infos.num + num; ++i)
				transfer.queueInfos.emplace_back(FamilyInfos::QueueInfos{ _famIndex, i });

			infos.num += num;
			reqs.transferNum -= num;
		}

		if (infos.num != 0)
			indexInfos.push_back(infos);
	}

	bool GraphicDeviceInfos::QueueFamiliesCompleted() const noexcept
	{
		return reqs.graphicNum == 0 &&
			reqs.computeNum == 0 &&
			reqs.transferNum == 0 &&
			reqs.presentNum == 0;
	}

	std::vector<VkDeviceQueueCreateInfo> GraphicDeviceInfos::GetDeviceCreateInfos() const noexcept
	{
		std::vector<VkDeviceQueueCreateInfo> result;
		result.reserve(indexInfos.size());

		static constexpr float queuePriority = 1.0f;

		for (auto it = indexInfos.begin(); it != indexInfos.end(); ++it)
		{
			// Create new queue create infos.
			VkDeviceQueueCreateInfo queueInfos{};
			queueInfos.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueInfos.pNext = nullptr;
			queueInfos.flags = 0;
			queueInfos.queueFamilyIndex = it->index;
			queueInfos.queueCount = it->num;
			queueInfos.pQueuePriorities = &queuePriority;

			result.emplace_back(queueInfos);
		}

		return result;
	}
}

#endif
