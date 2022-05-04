// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Buffers/VkABuffer.hpp>

#include <SA/Collections/Debug>

#include <Render/Vulkan/Device/VkDevice.hpp>

namespace Sa::Vk
{
	uint32_t ABuffer::FindMemoryType(const Device& _device, uint32_t _typeFilter, VkMemoryPropertyFlags _properties)
	{
		const VkPhysicalDeviceMemoryProperties& memProperties = _device.GetMemoryProperties();

		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
		{
			if ((_typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & _properties) == _properties)
				return i;
		}

		SA_ASSERT(Default, SA/Engine/Render/Vulkan, false, L"Memory type requiered not supported!");

		return ~uint32_t();
	}
}
