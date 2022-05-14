// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Buffers/ObjectBuffer/VkObjectBuffer.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>

namespace SA::VK
{
//{ Deleter

	ObjectBuffer::Deleter::Deleter(const Device& _device) noexcept : mDevice{ _device }
	{
	}

	void ObjectBuffer::Deleter::operator()(ObjectBuffer& _buffer) const
	{
		_buffer.Destroy(mDevice);
	}

//}

	ObjectBuffer::ObjectBuffer(ObjectBuffer&& _other) noexcept :
		mHandle{ _other.mHandle },
		mDeviceMemory{ _other.mDeviceMemory },
		mDeviceSize{ _other.mDeviceSize }
	{
		_other.mHandle = VK_NULL_HANDLE;
		_other.mDeviceMemory = VK_NULL_HANDLE;
		_other.mDeviceSize = 0u;
	}


	
	bool ObjectBuffer::IsValid() const noexcept
	{
		return mHandle != VK_NULL_HANDLE && mDeviceMemory != VK_NULL_HANDLE;
	}
	
	uint64_t ObjectBuffer::GetCapacity() const noexcept
	{
		return mDeviceSize;
	}

	
	VkBufferUsageFlags ObjectBuffer::GetUsage() const noexcept
	{
		return mUsage;
	}
	
	VkDescriptorType ObjectBuffer::GetDescriptorType() const noexcept
	{
		switch (mUsage)
		{
			case VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT:
				return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			case VK_BUFFER_USAGE_STORAGE_BUFFER_BIT:
				return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
			default:
			{
				SA_LOG(L"Usage [" << mUsage << L"] not supported yet!", Error, SA/Engine/Render/Vulkan);
				return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			}
		}
	}


	void ObjectBuffer::Create(const Device& _device,
		uint64_t _size, VkBufferUsageFlags _usage,
		VkMemoryPropertyFlags _properties)
	{
		mUsage = _usage;
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

		uint32_t memoryTypeIndex = FindMemoryType(_device, memRequirements.memoryTypeBits, _properties);

		VkMemoryAllocateInfo memoryAllocInfo{};
		memoryAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		memoryAllocInfo.pNext = nullptr;
		memoryAllocInfo.allocationSize = memRequirements.size;
		memoryAllocInfo.memoryTypeIndex = memoryTypeIndex;

		SA_VK_ASSERT(vkAllocateMemory(_device, &memoryAllocInfo, nullptr, &mDeviceMemory), L"Failed to allocate vertex buffer memory!");

		vkBindBufferMemory(_device, mHandle, mDeviceMemory, 0);
	}
	
	void ObjectBuffer::Destroy(const Device& _device)
	{
		SA_ASSERT(Default, SA/Render/Vulkan, IsValid(), L"Destroy a null Buffer!");

		vkDestroyBuffer(_device, mHandle, nullptr);
		vkFreeMemory(_device, mDeviceMemory, nullptr); // Should be freed after destroying buffer.

		mHandle = VK_NULL_HANDLE;
		mDeviceMemory = VK_NULL_HANDLE;
		mDeviceSize = 0u;
		mUsage = 0u;
	}


	VkDescriptorBufferInfo ObjectBuffer::CreateDescriptorBufferInfo() const noexcept
	{
		VkDescriptorBufferInfo descInfos{};
		descInfos.buffer = mHandle;
		descInfos.offset = 0u;
		descInfos.range = mDeviceSize;

		return descInfos;
	}


	ObjectBuffer::operator VkBuffer() const noexcept
	{
		return mHandle;
	}
	
	ObjectBuffer::operator VkDeviceMemory() const noexcept
	{
		return mDeviceMemory;
	}
}
