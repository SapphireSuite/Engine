// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Texture/VkTexture.hpp>

#include <Render/Base/Texture/Mipmap.hpp>

#include <Render/Vulkan/Buffers/VkBuffer.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	void Texture::Create(const Device& _device, CommandBuffer& _cmd, ResourceHolder& _resHold, const RawTexture& _raw)
	{
		uint64 dataSize = _raw.GetTotalSize();

		Buffer& stagingBuffer = _resHold.Make<Buffer>(Buffer::Deleter(_device));
		stagingBuffer.Create(_device, dataSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			_raw.data.data());


		ImageBufferCreateInfos imageBufferCreateInfos;

		imageBufferCreateInfos.imageFlags = 0u;
		imageBufferCreateInfos.imageType = ImageType::Image2D;

		imageBufferCreateInfos.format = _raw.format;
		imageBufferCreateInfos.extent = _raw.extent;

		imageBufferCreateInfos.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
		imageBufferCreateInfos.mipLevels = _raw.mipLevels;

		if (_raw.mipLevels > 1)
			imageBufferCreateInfos.usage |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;


		mBuffer.Create(_device, imageBufferCreateInfos);


		// Undef to Dst Transition
		{
			ImageBuffer::TransitionInfos infos{};
			infos.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			infos.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
			infos.mipLevels = _raw.mipLevels;
			infos.imageType = ImageType::Image2D;

			mBuffer.TransitionImageLayout(_cmd, _resHold, infos);

		}


		// Copy staging to device
		{
			ImageBuffer::CopyBufferImageInfos copyInfos{};
			copyInfos.buffer = stagingBuffer;
			copyInfos.extent = _raw.extent;
			copyInfos.format = _raw.format;
			copyInfos.mipLevels = _raw.mipLevels;
			copyInfos.imageType = ImageType::Image2D;

			mBuffer.CopyBufferToImage(_cmd, _resHold, copyInfos);
		}

		// Destroy will be called by ResourceHolder.
		//stagingBuffer.Destroy(device);


		// Dst to Read Transition
		{
			ImageBuffer::TransitionInfos infos{};
			infos.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
			infos.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			infos.mipLevels = _raw.mipLevels;
			infos.imageType = ImageType::Image2D;

			mBuffer.TransitionImageLayout(_cmd, _resHold, infos);
		}


		mSampler.Create(_device, _raw.mipLevels);
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