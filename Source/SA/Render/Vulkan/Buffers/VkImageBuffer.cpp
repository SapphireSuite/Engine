// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Buffers/VkImageBuffer.hpp>

#include <Core/Algorithms/SizeOf.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>

#include <Render/Vulkan/Device/VkDevice.hpp>

#include <Render/Vulkan/Buffers/VkBuffer.hpp>
#include <Render/Vulkan/Buffers/VkCommandBuffer.hpp>

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


	void ImageBuffer::TransitionImageLayout(CommandBuffer& _cmd, ResourceHolder& _resHold, const ImageBuffer::TransitionInfos& _infos)
	{
		VkImageMemoryBarrier& barrier = _resHold.Make<VkImageMemoryBarrier>();
		barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		barrier.pNext = nullptr;
		barrier.srcAccessMask = 0; // Set later.
		barrier.dstAccessMask = 0; // Set later.
		barrier.oldLayout = _infos.oldLayout;
		barrier.newLayout = _infos.newLayout;
		barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.image = mImage;
		barrier.subresourceRange.aspectMask = _infos.aspectFlags;
		barrier.subresourceRange.baseMipLevel = 0u;
		barrier.subresourceRange.levelCount = _infos.mipLevels;
		barrier.subresourceRange.baseArrayLayer = 0u;
		barrier.subresourceRange.layerCount = API_GetLayerNum(_infos.imageType);


		VkPipelineStageFlags srcStage = 0;
		VkPipelineStageFlags dstStage = 0;

		// Set stages and access mask.
		if (_infos.oldLayout == VK_IMAGE_LAYOUT_UNDEFINED)
		{
			srcStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;

			if (_infos.newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
			{
				barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

				dstStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
			}
			else if (_infos.newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
			{
				barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

				dstStage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
			}
		}
		else if (_infos.oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
		{
			if (_infos.newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
			{
				barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
				barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

				srcStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
				dstStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
			}
		}
		else
			SA_LOG(L"Unsupported image layout transition from [" << _infos.oldLayout << L"] to [" << _infos.newLayout << L"]!", Error, SA/Render/Vulkan);

		vkCmdPipelineBarrier(_cmd, srcStage, dstStage, 0, 0, nullptr, 0, nullptr, 1, &barrier);
	}
	
	void ImageBuffer::CopyBufferToImage(CommandBuffer& _cmd, ResourceHolder& _resHold, const ImageBuffer::CopyBufferImageInfos& _infos)
	{
		uint64 offset = 0u;
		VkExtent3D extent{ _infos.extent.x, _infos.extent.y, 1 };
		uint32 layerCount = API_GetLayerNum(_infos.imageType);
		uint32 channelNum = API_GetChannelNum(_infos.format);

		std::vector<VkBufferImageCopy>& bufferImageCopies = _resHold.Make<std::vector<VkBufferImageCopy>>();

		for (uint32 currMipLevel = 0u; currMipLevel < _infos.mipLevels; ++currMipLevel)
		{
			VkBufferImageCopy imageCopy{};
			imageCopy.bufferOffset = offset;
			imageCopy.bufferRowLength = 0u;
			imageCopy.bufferImageHeight = 0u;

			imageCopy.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			imageCopy.imageSubresource.mipLevel = currMipLevel;
			imageCopy.imageSubresource.baseArrayLayer = 0u;
			imageCopy.imageSubresource.layerCount = layerCount;

			imageCopy.imageOffset = VkOffset3D{ 0, 0, 0 };
			imageCopy.imageExtent = extent;

			bufferImageCopies.emplace_back(imageCopy);

			offset += extent.width * extent.height * channelNum;

			if (extent.width > 1)
				extent.width >>= 1;

			if (extent.height > 1)
				extent.height >>= 1;
		}

		vkCmdCopyBufferToImage(_cmd, _infos.buffer, mImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, SizeOf<uint32>(bufferImageCopies), bufferImageCopies.data());
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
