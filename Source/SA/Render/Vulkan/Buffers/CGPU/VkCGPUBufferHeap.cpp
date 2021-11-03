// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Buffers/CGPU/VkCGPUBufferHeap.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>

#include <Render/Vulkan/Buffers/CGPU/VkCGPUBuffer.hpp>
#include <Render/Vulkan/Buffers/CGPU/VkCGPUBufferLibrary.hpp>

namespace Sa::Vk
{
	void CGPUBufferHeap::Create(const Device& _device,
		VkBufferUsageFlags _usage,
		uint64 _size)
	{
		BufferHeap::Create(_device, _size, _usage, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	}


	uint64 CGPUBufferHeap::Allocate(const Device& _device, void* _data, uint64 _size)
	{
		MetaData* const meta = AllocateMeta(_device, _size);

		CGPUBufferLibrary::CopyData(_device, *this, _data, _size, meta->offset);

		return reinterpret_cast<uint64>(meta);
	}

	void CGPUBufferHeap::ReallocBuffer(const Device& _device, uint64 _newCapacity)
	{
		CGPUBuffer newBuffer;
		newBuffer.Create(_device, mUsage, _newCapacity);


		void* bufferData = nullptr;
		SA_VK_ASSERT(vkMapMemory(_device, mDeviceMemory, 0, mDeviceSize, 0, &bufferData), L"Fail to map memory");


		CGPUBufferLibrary::MoveData(_device, newBuffer, bufferData, mDeviceSize);


		vkUnmapMemory(_device, mDeviceMemory);


		Destroy(_device);
		static_cast<Buffer&>(*this) = std::move(newBuffer);
	}
}
