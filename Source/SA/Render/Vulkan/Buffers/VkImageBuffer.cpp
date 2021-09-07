// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Buffers/VkImageBuffer.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>

#include <Render/Vulkan/Device/VkDevice.hpp>

#include <Render/Vulkan/Buffers/VkBuffer.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	void ImageBuffer::CreateImage(const Device& _device, const VkImageCreateInfo& _vkInfos)
	{
		// Create Image.
		SA_VK_ASSERT(vkCreateImage(_device, &_vkInfos, nullptr, &mImage), L"Failed to create image!");


		// Create Image memory.
		VkMemoryRequirements memRequirements;
		vkGetImageMemoryRequirements(_device, mImage, &memRequirements);

		uint32 memoryTypeIndex = Buffer::FindMemoryType(_device, memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

		VkMemoryAllocateInfo memoryAllocInfo{};
		memoryAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		memoryAllocInfo.pNext = nullptr;
		memoryAllocInfo.allocationSize = memRequirements.size;
		memoryAllocInfo.memoryTypeIndex = memoryTypeIndex;

		SA_VK_ASSERT(vkAllocateMemory(_device, &memoryAllocInfo, nullptr, &mImageMemory), L"Failed to allocate image memory!");

		vkBindImageMemory(_device, mImage, mImageMemory, 0);
	}

	void ImageBuffer::CreateImageView(const Device& _device, const VkImageViewCreateInfo& _vkInfos)
	{
		SA_VK_ASSERT(vkCreateImageView(_device, &_vkInfos, nullptr, &mImageView), L"Failed to create image view!");
	}


	void ImageBuffer::Create(const Device& _device, const ImageBufferCreateInfos& _infos)
	{
		CreateImage(_device, _infos.VkImageInfos());
		CreateImageView(_device, _infos.VkImageViewInfos(mImage));
	}

	void ImageBuffer::CreateFromImage(const Device& _device, const ImageBufferCreateInfos& _infos, VkImage& _image)
	{
		mImage = _image;

		CreateImageView(_device, _infos.VkImageViewInfos(_image));
	}


	void ImageBuffer::Destroy(const Device& _device)
	{
		vkDestroyImageView(_device, mImageView, nullptr);
		mImageView = VK_NULL_HANDLE;

		// In case, the image was given to the buffer (using CreateFromImage).
		if (mImageMemory != VK_NULL_HANDLE)
		{
			vkDestroyImage(_device, mImage, nullptr);
			mImage = VK_NULL_HANDLE;

			// Free memory after destroying image: memory no more used.
			vkFreeMemory(_device, mImageMemory, nullptr);
			mImageMemory = VK_NULL_HANDLE;
		}
	}


	ImageBuffer::operator VkImage() const noexcept
	{
		return mImage;
	}
	
	ImageBuffer::operator VkImageView() const noexcept
	{
		return mImageView;
	}
	
	ImageBuffer::operator VkDeviceMemory() const noexcept
	{
		return mImageMemory;
	}
}

#endif
