// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Buffers/VkDeviceBuffer.hpp>

#include <Render/Vulkan/Buffers/VkBuffer.hpp>
#include <Render/Vulkan/Buffers/VkCommandBuffer.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	void DeviceBuffer::Create(const Device& _device,
		uint64 _size,
		VkBufferUsageFlags _usage)
	{
		Create_Internal(_device, _size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | _usage, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	}

	void DeviceBuffer::Create(const Device& _device,
		CommandBuffer& _cmdBuffer,
		uint64 _size,
		VkBufferUsageFlags _usage,
		const void* _data)
	{
		Create(_device, _size, _usage);

		UpdateData(_device, _cmdBuffer, _data, _size);
	}


	void DeviceBuffer::UpdateData(const Device& _device, CommandBuffer& _cmdBuffer, const void* _data, uint64 _size, uint64 _offset)
	{
		// Create temp staging buffer.
		Buffer stagingBuffer;
		stagingBuffer.Create(_device, _size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, _data);


		// Add copy command.
		VkBufferCopy copyRegion{};
		copyRegion.srcOffset = 0u;
		copyRegion.dstOffset = _offset;
		copyRegion.size = _size;

		vkCmdCopyBuffer(_cmdBuffer, stagingBuffer, mHandle, 1, &copyRegion);


		// Destroy staging buffer.
		stagingBuffer.Destroy(_device);
	}
}

#endif
