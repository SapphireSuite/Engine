// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Buffers/VkGPUBuffer.hpp>

#include <Render/Vulkan/Device/VkDevice.hpp>
#include <Render/Vulkan/VkResourceInitializer.hpp>
#include <Render/Vulkan/Buffers/VkBuffer.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	bool GPUBuffer::IsValid() const noexcept
	{
		return mHandle.IsValid();
	}


	void GPUBuffer::Create(const ARenderDevice* _device,
		RenderBufferType _type,
		uint64 _size)
	{
		mHandle.Create(_device->As<Device>(),
			_size,
			VK_BUFFER_USAGE_TRANSFER_DST_BIT | API_GetBufferUsage(_type),
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
		);
	}

	void GPUBuffer::Create(ARenderResourceInitializer& _init,
		RenderBufferType _type,
		uint64 _size,
		const void* _data)
	{
		Create(_init.As<ResourceInitializer>().device, _type, _size);

		UpdateData(_init, _data, _size);
	}

	void GPUBuffer::Destroy(const ARenderDevice* _device)
	{
		mHandle.Destroy(_device->As<Device>());
	}


	void GPUBuffer::UpdateData(ARenderResourceInitializer& _init, const void* _data, uint64 _size, uint64 _offset)
	{
		ResourceInitializer& vkInit = _init.As<ResourceInitializer>();

		// Create temp staging buffer. Hold buffer until command is submitted and executed.
		Buffer& stagingBuffer = Buffer::CreateStaging(vkInit, _data, _size);


		// Add copy command.
		VkBufferCopy copyRegion{};
		copyRegion.srcOffset = 0u;
		copyRegion.dstOffset = _offset;
		copyRegion.size = _size;

		vkCmdCopyBuffer(vkInit.cmd, stagingBuffer, mHandle, 1, &copyRegion);


		// Destroy will be called by ResourceHolder.
		//stagingBuffer.Destroy(_device);
	}


	GPUBuffer::operator VkBuffer() const noexcept
	{
		return mHandle;
	}
}

#endif
