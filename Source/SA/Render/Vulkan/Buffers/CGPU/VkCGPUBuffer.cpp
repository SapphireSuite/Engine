// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Buffers/CGPU/VkCGPUBuffer.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>
#include <Render/Vulkan/Buffers/CGPU/VkCGPUBufferLibrary.hpp>
#include <Render/Vulkan/VkResourceInitializer.hpp>

namespace Sa::Vk
{
	void CGPUBuffer::Create(const Device& _device,
		VkBufferUsageFlags _usage,
		uint64 _size,
		const void* _data)
	{
		Buffer::Create(_device, _size, _usage,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		UpdateData(_device, _data, _size);
	}

	void CGPUBuffer::UpdateData(const Device& _device, const void* _data, uint64 _size, uint64 _offset)
	{
		if(_data)
			CGPUBufferLibrary::CopyData(_device, *this, _data, _size, _offset);
		else
			CGPUBufferLibrary::ResetData(_device, *this, _size, _offset);
	}


	CGPUBuffer& CGPUBuffer::CreateStaging(const Device& _device, ResourceInitializer& _init, const void* _data, uint64 _size)
	{
		CGPUBuffer& stagingBuffer = _init.resHolder.Make<CGPUBuffer>(Buffer::Deleter(_device));

		stagingBuffer.Create(_device,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			_size,
			_data
		);

		return stagingBuffer;
	}
}
