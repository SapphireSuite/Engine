// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Texture/VkTexture.hpp>

#include <Render/Base/Texture/Mipmap.hpp>

#include <Render/Vulkan/Device/VkDevice.hpp>
#include <Render/Vulkan/Context/VkResourceInitializer.hpp>
#include <Render/Vulkan/Buffers/ObjectBuffer/CGPU/VkCGPUBuffer.hpp>

namespace SA::VK
{
	void Texture::Create(const Device& _device, ResourceInitializer& _init, const RawTexture& _raw)
	{
		ObjectBuffer& stagingBuffer = CGPUBuffer::CreateStaging(_device, _init, _raw.data.data(), _raw.GetTotalSize());


		// Create Device Image buffer
		{
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
		}


		// Undef to Dst Transition
		{
			ImageBuffer::TransitionInfos infos{};
			infos.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			infos.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
			infos.mipLevels = _raw.mipLevels;
			infos.imageType = ImageType::Image2D;

			mBuffer.TransitionImageLayout(_init, infos);

		}


		// Copy staging to device
		{
			ImageBuffer::CopyBufferImageInfos copyInfos{};
			copyInfos.buffer = stagingBuffer;
			copyInfos.extent = _raw.extent;
			copyInfos.format = _raw.format;
			copyInfos.mipLevels = _raw.mipLevels;
			copyInfos.imageType = ImageType::Image2D;

			mBuffer.CopyBufferToImage(_init, copyInfos);
		}


		// Dst to Read Transition
		{
			ImageBuffer::TransitionInfos infos{};
			infos.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
			infos.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			infos.mipLevels = _raw.mipLevels;
			infos.imageType = ImageType::Image2D;

			mBuffer.TransitionImageLayout(_init, infos);
		}


		// Destroy will be called by ResourceHolder.
		//stagingBuffer.Destroy(device);

		mSampler.Create(_device, _raw.mipLevels);
		
		SA_LOG(L"Texture created.", Infos, SA/Engine/Render/Vulkan);
	}

	void Texture::Destroy(const Device& _device)
	{
		mSampler.Destroy(_device);

		mBuffer.Destroy(_device);
		
		SA_LOG(L"Texture destroyed.", Infos, SA/Engine/Render/Vulkan);
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
