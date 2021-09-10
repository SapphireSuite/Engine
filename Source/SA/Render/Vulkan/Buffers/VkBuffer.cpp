// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Buffers/VkBuffer.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	void Buffer::Create(const Device& _device,
		uint64 _size, VkBufferUsageFlags _usage,
		VkMemoryPropertyFlags _properties,
		const void* _data)
	{
		SA_ASSERT(Default, SA/Render/Vulkan, _properties != VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, L"Use Vk::DeviceBuffer for local device buffer.");

		Create_Internal(_device, _size, _usage, _properties);

		UpdateData(_device, _data, _size);
	}


	void Buffer::UpdateData(const Device& _device, const void* _data, uint64 _size, uint64 _offset)
	{
		void* bufferData = nullptr;

		SA_VK_ASSERT(vkMapMemory(_device, mDeviceMemory, _offset, _size, 0, &bufferData), L"Fail to map memory");

		if(_data)
			std::memcpy(bufferData, _data, _size);
		else
			std::memset(bufferData, 0, _size);

		vkUnmapMemory(_device, mDeviceMemory);
	}
}

#endif
