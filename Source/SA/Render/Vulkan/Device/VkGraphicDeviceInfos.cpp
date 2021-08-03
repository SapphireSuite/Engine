// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Device/VkGraphicDeviceInfos.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Surface/VkRenderSurface.hpp>

namespace Sa::Vk
{
	bool GraphicDeviceInfos::FamilyInfos::IsCompleted() const noexcept
	{
		return index != ~uint32();
	}


	GraphicDeviceInfos::GraphicDeviceInfos(VkPhysicalDevice _device, QueueType _familyTypes) noexcept :
		device{ _device },
		familyTypes{ _familyTypes }
	{
		VkPhysicalDeviceProperties properties;
		vkGetPhysicalDeviceProperties(device, &properties);

		ID = properties.deviceID;
		name = properties.deviceName;
	}


	const GraphicDeviceInfos::FamilyInfos* GraphicDeviceInfos::Families() const noexcept
	{
		return &graphics;
	}

	void GraphicDeviceInfos::QueryQueueFamilies(const RenderSurface* _surface) noexcept
	{
		SA_ASSERT(Default, SA/Render/Vulkan, device != VK_NULL_HANDLE, L"Query queue families of a null physical device!");

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		for (uint32 i = 0; i < queueFamilies.size(); ++i)
			AddFamily(_surface, queueFamilies[i], i);
	}

	void GraphicDeviceInfos::AddFamily(const RenderSurface* _surface, const VkQueueFamilyProperties& _family, uint32 _index) noexcept
	{
		// Present family. Should be checked first.
		if (_surface && (familyTypes & QueueType::Present))
		{
			if (present.index == ~uint32() ||				// Not completed yet.
				graphics.index != _index)					// Different from graphics.
			{
				VkBool32 presentSupport = false;
				SA_VK_ASSERT(vkGetPhysicalDeviceSurfaceSupportKHR(device, _index, *_surface, &presentSupport));

				if (presentSupport)
					present.index = _index;
			}
		}


		// Graphics family.
		if (familyTypes & QueueType::Graphics && (_family.queueFlags & VK_QUEUE_GRAPHICS_BIT))
		{
			if (graphics.index == ~uint32() ||					// Not completed yet.
				graphics.maxQueueNum < _family.queueCount)		// Allow more queue simultaneously.
			{
				graphics.index = _index;
				graphics.maxQueueNum = _family.queueCount;
			}
		}


		// Compute family.
		if (familyTypes & QueueType::Compute && (_family.queueFlags & VK_QUEUE_COMPUTE_BIT))
		{
			if (compute.index == ~uint32() ||					// Not completed yet.
				present.index != _index)						// Different from Present.
			{
				compute.index = _index;
				compute.maxQueueNum = _family.queueCount;
			}
		}


		// Transfer family.
		if (familyTypes & QueueType::Transfer && (_family.queueFlags & VK_QUEUE_TRANSFER_BIT))
		{
			if (transfer.index == ~uint32() ||				// Not completed yet.
				(graphics.index != _index &&				// Different from Graphics.
				present.index != _index))					// Different from Present.
			{
				transfer.index = _index;
				transfer.maxQueueNum = _family.queueCount;
			}
		}
	}

	bool GraphicDeviceInfos::QueueFamiliesCompleted() const noexcept
	{
		const FamilyInfos* const families = Families();

		// Check each family in type.
		for (uint32 i = 0u; i < familyNum; ++i)
		{
			// Has requiered type.
			if (static_cast<uint32>(familyTypes) & (1 << i))
			{
				// At least one requiered family not completed.
				if (!families[i].IsCompleted())
					return false;
			}
		}

		return true;
	}


	std::vector<VkDeviceQueueCreateInfo> GraphicDeviceInfos::GetDeviceCreateInfos() const noexcept
	{
		std::vector<VkDeviceQueueCreateInfo> result;
		result.reserve(5u);

		static constexpr float queuePriority = 1.0f;
		const FamilyInfos* const families = Families();

		for (uint32 i = 0u; i < familyNum; ++i)
		{
			// Has current type.
			if ((static_cast<uint32>(familyTypes) & (1 << i)) == 0)
				continue;

			SA_WARN(!families[i].IsCompleted(), SA/Render/Vulkan, L"Create device infos of an uncompleted family!");

			// Family index already in results.
			bool bFound = false;

			for (auto it = result.begin(); it != result.end(); ++it)
			{
				// Family index found.
				if (it->queueFamilyIndex == families[i].index)
				{
					// Add queueNum.
					it->queueCount = std::max(it->queueCount + families[i].queueNum, families[i].maxQueueNum);

					bFound = true;
				}
			}

			if (bFound)
				continue;


			// Create new queue create infos.
			VkDeviceQueueCreateInfo queueInfos{};
			queueInfos.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueInfos.pNext = nullptr;
			queueInfos.flags = 0;
			queueInfos.queueFamilyIndex = families[i].index;
			queueInfos.queueCount = families[i].queueNum;
			queueInfos.pQueuePriorities = &queuePriority;

			result.emplace_back(queueInfos);
		}

		return result;
	}
}
