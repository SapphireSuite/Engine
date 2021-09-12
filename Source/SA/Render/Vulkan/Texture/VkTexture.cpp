// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Texture/VkTexture.hpp>

#include <Render/Base/Texture/Mipmap.hpp>

#include <Render/Vulkan/Buffers/VkBuffer.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	void Texture::Create(const Device& _device, CommandBuffer& _cmd, ResourceHolder& _resHold, const RawTexture& _rawTexture)
	{
		uint64 dataSize = _rawTexture.GetTotalSize();

		Buffer& stagingBuffer = _resHold.Make<Buffer>(Buffer::Deleter(_device));
		stagingBuffer.Create(_device, dataSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			_rawTexture.data.data());


		ImageBufferCreateInfos imageBufferCreateInfos;

		imageBufferCreateInfos.imageFlags = 0u;
		imageBufferCreateInfos.imageType = ImageType::Image2D;

		imageBufferCreateInfos.format = _rawTexture.format;
		imageBufferCreateInfos.extent = _rawTexture.extent;

		imageBufferCreateInfos.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
		imageBufferCreateInfos.mipLevels = _rawTexture.mipLevels;

		if (_rawTexture.mipLevels > 1)
			imageBufferCreateInfos.usage |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;


		mBuffer.Create(_device, imageBufferCreateInfos);


		ImageBuffer::CopyBufferImageInfos copyInfos{};
		copyInfos.buffer = stagingBuffer;
		copyInfos.extent = _rawTexture.extent;
		copyInfos.format = _rawTexture.format;
		copyInfos.mipLevels = _rawTexture.mipLevels;
		copyInfos.imageType = ImageType::Image2D;

		mBuffer.CopyBufferToImage(_cmd, _resHold, copyInfos);

		// Destroy will be called by ResourceHolder.
		//stagingBuffer.Destroy(device);


		ImageBuffer::TransitionInfos dstToReadTransitionInfos{};
		dstToReadTransitionInfos.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		dstToReadTransitionInfos.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		dstToReadTransitionInfos.mipLevels = _rawTexture.mipLevels;
		dstToReadTransitionInfos.imageType = ImageType::Image2D;

		mBuffer.TransitionImageLayout(_cmd, _resHold, dstToReadTransitionInfos);


		mSampler.Create(_device, _rawTexture.mipLevels);
	}

	void Texture::Destroy(const Device& _device)
	{
		mSampler.Destroy(_device);

		mBuffer.Destroy(_device);
	}

	VkDescriptorImageInfo Texture::CreateDescriptorImageInfo() const noexcept
	{
		VkDescriptorImageInfo descImage{};
		descImage.sampler = mSampler;
		descImage.imageView = mBuffer;
		descImage.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

		return descImage;
	}
}

#endif
