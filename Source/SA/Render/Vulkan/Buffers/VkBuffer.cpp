// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Buffers/VkBuffer.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>
#include <Render/Vulkan/VkResourceInitializer.hpp>

namespace Sa::Vk
{
	Buffer::Deleter::Deleter(const Device& _device) noexcept : mDevice{ _device }
	{
	}

	void Buffer::Deleter::operator()(Buffer& _buffer)
	{
		_buffer.Destroy(mDevice);
	}


	void Buffer::Create(const Device& _device,
		VkBufferUsageFlags _usage,
		uint64 _size,
		const void* _data)
	{
		Create_Internal(_device,
			_size,
			_usage,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
		);

		UpdateData(_device, _data, _size);
	}

	void Buffer::UpdateData(const Device& _device, const void* _data, uint64 _size, uint64 _offset)
	{
		void* bufferData = nullptr;

		SA_VK_ASSERT(vkMapMemory(_device, mDeviceMemory, _offset, _size, 0, &bufferData), L"Fail to map memory");

		if(_data)
			std::memcpy(bufferData, _data, _size);
		else
			std::memset(bufferData, 0, _size);

		vkUnmapMemory(_device, mDeviceMemory);
	}


	Buffer& Buffer::CreateStaging(const Device& _device, ResourceInitializer& _init, const void* _data, uint64 _size)
	{
		Buffer& stagingBuffer = _init.resHolder.Make<Buffer>(Buffer::Deleter(_device));

		stagingBuffer.Create(_device,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			_size,
			_data
		);

		return stagingBuffer;
	}
}
