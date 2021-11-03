// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Buffers/VkBuffer.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>

namespace Sa::Vk
{
//{ Deleter

	Buffer::Deleter::Deleter(const Device& _device) noexcept : mDevice{ _device }
	{
	}

	void Buffer::Deleter::operator()(Buffer& _buffer) const
	{
		_buffer.Destroy(mDevice);
	}

//}

	bool Buffer::IsValid() const noexcept
	{
		return mHandle != VK_NULL_HANDLE && mDeviceMemory != VK_NULL_HANDLE;
	}


	void Buffer::Create(const Device& _device,
		uint64 _size, VkBufferUsageFlags _usage,
		VkMemoryPropertyFlags _properties)
	{
		mDeviceSize = _size;

		VkBufferCreateInfo bufferInfo{};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.pNext = nullptr;
		bufferInfo.flags = 0u;
		bufferInfo.size = _size;
		bufferInfo.usage = _usage;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		bufferInfo.queueFamilyIndexCount = 0u;
		bufferInfo.pQueueFamilyIndices = nullptr;

		SA_VK_ASSERT(vkCreateBuffer(_device, &bufferInfo, nullptr, &mHandle), L"Failed to create vertex buffer!");


		// === Memory ===
		VkMemoryRequirements memRequirements{};
		vkGetBufferMemoryRequirements(_device, mHandle, &memRequirements);

		uint32 memoryTypeIndex = FindMemoryType(_device, memRequirements.memoryTypeBits, _properties);

		VkMemoryAllocateInfo memoryAllocInfo{};
		memoryAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		memoryAllocInfo.pNext = nullptr;
		memoryAllocInfo.allocationSize = memRequirements.size;
		memoryAllocInfo.memoryTypeIndex = memoryTypeIndex;

		SA_VK_ASSERT(vkAllocateMemory(_device, &memoryAllocInfo, nullptr, &mDeviceMemory), L"Failed to allocate vertex buffer memory!");

		vkBindBufferMemory(_device, mHandle, mDeviceMemory, 0);
	}

	void Buffer::Destroy(const Device& _device)
	{
		SA_ASSERT(Default, SA/Render/Vulkan, IsValid(), L"Destroy a null Buffer!");

		vkDestroyBuffer(_device, mHandle, nullptr);
		vkFreeMemory(_device, mDeviceMemory, nullptr); // Should be freed after destroying buffer.

		mHandle = VK_NULL_HANDLE;
		mDeviceMemory = VK_NULL_HANDLE;
		mDeviceSize = 0u;
	}


	VkDescriptorBufferInfo Buffer::CreateDescriptorBufferInfo() const noexcept
	{
		VkDescriptorBufferInfo descInfos{};
		descInfos.buffer = mHandle;
		descInfos.offset = 0u;
		descInfos.range = mDeviceSize;

		return descInfos;
	}


	uint32 Buffer::FindMemoryType(const Device& _device, uint32 _typeFilter, VkMemoryPropertyFlags _properties)
	{
		const VkPhysicalDeviceMemoryProperties& memProperties = _device.GetMemoryProperties();

		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
		{
			if ((_typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & _properties) == _properties)
				return i;
		}

		SA_ASSERT(Default, SA/Render/Vulkan, false, L"Memory type requiered not supported!");

		return ~uint32();
	}


	Buffer& Buffer::operator=(Buffer&& _rhs)
	{
		SA_ASSERT(Default, SA/Render/Vulkan, !IsValid(), L"Current buffer must be destroyed before new assignation!");

		mHandle = _rhs.mHandle;
		mDeviceMemory = _rhs.mDeviceMemory;
		mDeviceSize = _rhs.mDeviceSize;

		_rhs.mHandle = VK_NULL_HANDLE;
		_rhs.mDeviceMemory = VK_NULL_HANDLE;
		_rhs.mDeviceSize = 0u;

		return *this;
	}


	Buffer::operator VkBuffer() const noexcept
	{
		return mHandle;
	}

	Buffer::operator VkDeviceMemory() const noexcept
	{
		return mDeviceMemory;
	}
}
