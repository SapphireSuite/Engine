// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Texture/VkCubemap.hpp>

#include <Render/Vulkan/VkResourceInitializer.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>
#include <Render/Vulkan/Buffers/VkBuffer.hpp>

namespace Sa::Vk
{
	void Cubemap::Create(const Device& _device, ResourceInitializer& _init, const RawCubemap& _raw)
	{
		Buffer& stagingBuffer = Buffer::CreateStaging(_device, _init, _raw.data.data(), _raw.GetTotalMapSize());


		ImageBufferCreateInfos imageBufferCreateInfos;

		imageBufferCreateInfos.imageType = ImageType::Cube;

		imageBufferCreateInfos.format = _raw.format;
		imageBufferCreateInfos.extent = _raw.extent;

		imageBufferCreateInfos.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
		imageBufferCreateInfos.mipLevels = _raw.mipLevels;

		if (_raw.mipLevels > 1)
			imageBufferCreateInfos.usage |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;

		
		// === Create buffer ===
		mBuffer.Create(_device, imageBufferCreateInfos);

		// Copy image to shader.
		ImageBuffer::TransitionInfos undefToDstTransitionInfos{};
		undefToDstTransitionInfos.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		undefToDstTransitionInfos.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		undefToDstTransitionInfos.mipLevels = _raw.mipLevels;
		undefToDstTransitionInfos.imageType = ImageType::Cube;

		mBuffer.TransitionImageLayout(_init, undefToDstTransitionInfos);


		ImageBuffer::CopyBufferImageInfos copyInfos{};
		copyInfos.buffer = stagingBuffer;
		copyInfos.extent = _raw.extent;
		copyInfos.format = _raw.format;
		copyInfos.mipLevels = _raw.mipLevels;
		copyInfos.imageType = ImageType::Cube;

		mBuffer.CopyBufferToImage(_init, copyInfos);


		ImageBuffer::TransitionInfos dstToReadTransitionInfos{};
		dstToReadTransitionInfos.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		dstToReadTransitionInfos.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		dstToReadTransitionInfos.mipLevels = _raw.mipLevels;
		dstToReadTransitionInfos.imageType = ImageType::Cube;

		mBuffer.TransitionImageLayout(_init, dstToReadTransitionInfos);


		// Destroy will be called by ResourceHolder.
		//stagingBuffer.Destroy(device);


		// === Create irradiance buffer ===
		Buffer& irrStagingBuffer = Buffer::CreateStaging(_device, _init, _raw.data.data(), _raw.GetMapSize());

		imageBufferCreateInfos.mipLevels = 1u;
		imageBufferCreateInfos.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

		copyInfos.mipLevels = 1u;
		copyInfos.buffer = irrStagingBuffer;
		undefToDstTransitionInfos.mipLevels = 1u;
		dstToReadTransitionInfos.mipLevels = 1u;


		mIrradianceBuffer.Create(_device, imageBufferCreateInfos);

		mIrradianceBuffer.TransitionImageLayout(_init, undefToDstTransitionInfos);

		mIrradianceBuffer.CopyBufferToImage(_init, copyInfos);

		mIrradianceBuffer.TransitionImageLayout(_init, dstToReadTransitionInfos);


		// Destroy will be called by ResourceHolder.
		//irrStagingBuffer.Destroy(device);


		mSampler.Create(_device, _raw.mipLevels);
		
		SA_LOG(L"Cubemap created.", Infos, SA/Render/Vulkan);
	}

	void Cubemap::Destroy(const Device& _device)
	{
		mSampler.Destroy(_device);

		mBuffer.Destroy(_device);
		mIrradianceBuffer.Destroy(_device);
		
		SA_LOG(L"Cubemap destroyed.", Infos, SA/Render/Vulkan);
	}


	VkDescriptorImageInfo Cubemap::CreateDescriptorImageInfo() const noexcept
	{
		VkDescriptorImageInfo descImage{};
		descImage.sampler = mSampler;
		descImage.imageView = mBuffer;
		descImage.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

		return descImage;
	}

	VkDescriptorImageInfo Cubemap::CreateIrradianceDescriptorImageInfo() const noexcept
	{
		VkDescriptorImageInfo descImage{};
		descImage.sampler = mSampler;
		descImage.imageView = mIrradianceBuffer;
		descImage.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

		return descImage;
	}

	VkWriteDescriptorSet Cubemap::CreateWriteDescriptorSet(VkDescriptorSet _descriptorSet, uint32 _binding, uint32 _arrayElem) noexcept
	{
		VkWriteDescriptorSet writeDesc{};
		writeDesc.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		writeDesc.pNext = nullptr;
		writeDesc.dstSet = _descriptorSet;
		writeDesc.dstBinding = _binding;
		writeDesc.dstArrayElement = _arrayElem;
		writeDesc.descriptorCount = 1u;
		writeDesc.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		writeDesc.pImageInfo = nullptr; // Will be set in pipeline.
		writeDesc.pBufferInfo = nullptr; // Will be set in pipeline.
		writeDesc.pTexelBufferView = nullptr; // Will be set in pipeline.

		return writeDesc;
	}
}
