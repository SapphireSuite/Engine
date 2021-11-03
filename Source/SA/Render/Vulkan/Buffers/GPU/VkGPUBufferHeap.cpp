// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Buffers/GPU/VkGPUBufferHeap.hpp>

#include <Render/Vulkan/VkResourceInitializer.hpp>
#include <Render/Vulkan/Buffers/GPU/VkGPUBufferLibrary.hpp>

namespace Sa::Vk
{
	void GPUBufferHeap::Create(const Device& _device,
		VkBufferUsageFlags _usage,
		uint64 _size)
	{
		BufferHeap::Create(_device, _size,
			VK_BUFFER_USAGE_TRANSFER_DST_BIT | _usage,
			GPUBufferLibrary::defaultProperties);
	}


	uint64 GPUBufferHeap::Allocate(const Device& _device, ResourceInitializer& _init, void* _data, uint64 _size)
	{
		MetaData* const meta = AllocateMeta(_device, _size, &_init);

		GPUBufferLibrary::CopyData(_device, _init , _data, *this, _size, meta->offset);

		return reinterpret_cast<uint64>(meta);
	}

	void GPUBufferHeap::ReallocBuffer(const Device& _device, uint64 _newCapacity, ResourceInitializer* _init)
	{
		GPUBufferHeap& oldBuffer = _init->resHolder.Make<GPUBufferHeap>(Buffer::Deleter(_device));

		// Move buffer handles only.
		static_cast<Buffer&>(oldBuffer) = std::move(static_cast<Buffer&>(*this));


		Buffer newBuffer;
		newBuffer.Create(_device, _newCapacity, mUsage, GPUBufferLibrary::defaultProperties);

		GPUBufferLibrary::CopyData(*_init, oldBuffer, newBuffer);


		// This buffer is empty due to move into oldBuffer. No need for destroy.
		//Destroy(_device);


		// Move new allocated handles.
		static_cast<Buffer&>(*this) = std::move(newBuffer);
	}
}
