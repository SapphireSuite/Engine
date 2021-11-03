// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Buffers/GPU/VkGPUBuffer.hpp>

#include <Render/Vulkan/Buffers/GPU/VkGPUBufferLibrary.hpp>

namespace Sa::Vk
{
	void GPUBuffer::Create(const Device& _device,
		VkBufferUsageFlags _usage,
		uint64 _size)
	{
		Buffer::Create(_device, _size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | _usage, GPUBufferLibrary::defaultProperties);
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
		GPUBufferLibrary::CopyData(_device, _init , _data , *this, _size, _offset);
	}
}
