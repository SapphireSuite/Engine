// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Buffers/ObjectBuffer/GPU/VkGPUBuffer.hpp>

#include <Render/Vulkan/Buffers/ObjectBuffer/GPU/VkGPUBufferLibrary.hpp>

namespace SA::VK
{
	void GPUBuffer::Create(const Device& _device,
		VkBufferUsageFlags _usage,
		uint64_t _size)
	{
		ObjectBuffer::Create(_device, _size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | _usage, GPUBufferLibrary::defaultProperties);
	}

	void GPUBuffer::Create(const Device& _device,
		ResourceInitializer& _init,
		VkBufferUsageFlags _usage,
		uint64_t _size,
		const void* _data)
	{
		Create(_device, _usage, _size);

		UpdateData(_device, _init, _data, _size);
	}


	void GPUBuffer::UpdateData(const Device& _device, ResourceInitializer& _init, const void* _data, uint64_t _size, uint64_t _offset)
	{
		GPUBufferLibrary::CopyData(_device, _init , _data , *this, _size, _offset);
	}
}
