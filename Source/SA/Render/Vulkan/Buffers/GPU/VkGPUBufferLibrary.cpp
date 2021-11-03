// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Buffers/GPU/VkGPUBufferLibrary.hpp>

#include <Render/Vulkan/VkResourceInitializer.hpp>
#include <Render/Vulkan/Buffers/CGPU/VkCGPUBuffer.hpp>

namespace Sa::Vk
{
	void GPUBufferLibrary::CopyData(const Device& _device, Buffer& _buffer, ResourceInitializer& _init, const void* _src, uint64 _size, uint64 _offset)
	{
		// Create temp staging buffer. Hold buffer until command is submitted and executed.
		CGPUBuffer& stagingBuffer = CGPUBuffer::CreateStaging(_device, _init, _src, _size);


		// Add copy command.
		VkBufferCopy copyRegion{};
		copyRegion.srcOffset = 0u;
		copyRegion.dstOffset = _offset;
		copyRegion.size = _size;

		vkCmdCopyBuffer(_init.cmd, stagingBuffer, _buffer, 1, &copyRegion);


		// Destroy will be called by ResourceHolder.
		//stagingBuffer.Destroy(_device);
	}
}
