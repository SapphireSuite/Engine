// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Buffers/ObjectBuffer/CGPU/VkCGPUBuffer.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>
#include <Render/Vulkan/Context/VkResourceInitializer.hpp>

#include <Render/Vulkan/Buffers/ObjectBuffer/CGPU/VkCGPUBufferLibrary.hpp>

namespace SA::VK
{
	void CGPUBuffer::Create(const Device& _device,
		VkBufferUsageFlags _usage,
		uint64_t _size,
		const void* _data)
	{
		ObjectBuffer::Create(_device, _size, _usage, CGPUBufferLibrary::defaultProperties);

		UpdateData(_device, _data, _size);
	}

	void CGPUBuffer::UpdateData(const Device& _device, const void* _data, uint64_t _size, uint64_t _offset)
	{
		if(_data)
			CGPUBufferLibrary::CopyData(_device, *this, _data, _size, _offset);
		else
			CGPUBufferLibrary::ResetData(_device, *this, _size, _offset);
	}


	CGPUBuffer& CGPUBuffer::CreateStaging(const Device& _device, ResourceInitializer& _init, const void* _data, uint64_t _size)
	{
		CGPUBuffer& stagingBuffer = _init.resHolder.Make<CGPUBuffer>(ObjectBuffer::Deleter(_device));

		stagingBuffer.Create(_device,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			_size,
			_data
		);

		return stagingBuffer;
	}
}
