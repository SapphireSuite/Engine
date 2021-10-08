// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Buffers/VkBuffer.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>
#include <Render/Vulkan/VkResourceInitializer.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	bool Buffer::IsValid() const noexcept
	{
		return mHandle.IsValid();
	}


	void Buffer::Create(const ARenderDevice* _device,
		RenderBufferType _type,
		uint64 _size,
		const void* _data)
	{
		mHandle.Create(_device->As<Device>(),
			_size,
			API_GetBufferUsage(_type),
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
		);

		UpdateData(_device, _data, _size);
	}

	void Buffer::Destroy(const ARenderDevice* _device)
	{
		mHandle.Destroy(_device->As<Device>());
	}


	void Buffer::UpdateData(const ARenderDevice* _device, const void* _data, uint64 _size, uint64 _offset)
	{
		const Device& vkDevice = _device->As<Device>();

		void* bufferData = nullptr;

		SA_VK_ASSERT(vkMapMemory(vkDevice, mHandle, _offset, _size, 0, &bufferData), L"Fail to map memory");

		if(_data)
			std::memcpy(bufferData, _data, _size);
		else
			std::memset(bufferData, 0, _size);

		vkUnmapMemory(vkDevice, mHandle);
	}


	Buffer& Buffer::CreateStaging(ResourceInitializer& _init, const void* _data, uint64 _size)
	{
		Buffer& stagingBuffer = _init.resHolder.Make<Buffer>(Buffer::Deleter(_init.device));

		stagingBuffer.Create(_init.device,
			RenderBufferType::TransferSRC,
			_size,
			_data
		);

		return stagingBuffer;
	}


	Buffer::operator VkBuffer() const noexcept
	{
		return mHandle;
	}
}

#endif
