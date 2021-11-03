// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Buffers/GPU/VkGPUBuffer.hpp>

#include <Render/Vulkan/VkResourceInitializer.hpp>

namespace Sa::Vk
{
	void GPUBuffer::Create(const Device& _device,
		VkBufferUsageFlags _usage,
		uint64 _size)
	{
		Buffer::Create(_device, _size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | _usage, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	}

	void GPUBuffer::Create(const Device& _device,
		ResourceInitializer& _init,
		VkBufferUsageFlags _usage,
		uint64 _size,
		const void* _data)
	{
		Create(_device, _usage, _size);

		UpdateData(_device, _init, _data, _size);
	}


	void GPUBuffer::UpdateData(const Device& _device, ResourceInitializer& _init, const void* _data, uint64 _size, uint64 _offset)
	{
		// TODO: implement

		//// Create temp staging buffer. Hold buffer until command is submitted and executed.
		//Buffer& stagingBuffer = Buffer::CreateStaging(_device, _init, _data, _size);


		//// Add copy command.
		//VkBufferCopy copyRegion{};
		//copyRegion.srcOffset = 0u;
		//copyRegion.dstOffset = _offset;
		//copyRegion.size = _size;

		//vkCmdCopyBuffer(_init.cmd, stagingBuffer, mHandle, 1, &copyRegion);


		// Destroy will be called by ResourceHolder.
		//stagingBuffer.Destroy(_device);
	}
}
