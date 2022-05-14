// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Buffers/ObjectBuffer/GPU/VkGPUBufferLibrary.hpp>

#include <Render/Vulkan/Context/VkResourceInitializer.hpp>
#include <Render/Vulkan/Buffers/ObjectBuffer/CGPU/VkCGPUBuffer.hpp>

namespace SA::VK
{
	void GPUBufferLibrary::CopyData(ResourceInitializer& _init, const ObjectBuffer& _src, ObjectBuffer& _dst)
	{
		// Add copy command.
		VkBufferCopy copyRegion{};
		copyRegion.srcOffset = 0u;
		copyRegion.dstOffset = 0u;
		copyRegion.size = _src.GetCapacity();

		vkCmdCopyBuffer(_init.cmd, _src, _dst, 1, &copyRegion);
	}

	void GPUBufferLibrary::CopyData(const Device& _device,
		ResourceInitializer& _init,
		const void* _src,
		ObjectBuffer& _dst,
		uint64_t _size,
		uint64_t _dstOffset)
	{
		// Create temp staging buffer. Hold buffer until command is submitted and executed.
		CGPUBuffer& stagingBuffer = CGPUBuffer::CreateStaging(_device, _init, _src, _size);


		// Add copy command.
		VkBufferCopy copyRegion{};
		copyRegion.srcOffset = 0u;
		copyRegion.dstOffset = _dstOffset;
		copyRegion.size = _size;

		vkCmdCopyBuffer(_init.cmd, stagingBuffer, _dst, 1, &copyRegion);


		// Destroy will be called by ResourceHolder.
		//stagingBuffer.Destroy(_device);
	}
}
