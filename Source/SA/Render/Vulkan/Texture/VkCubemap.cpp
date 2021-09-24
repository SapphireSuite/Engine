// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Texture/VkCubemap.hpp>

#include <Render/Vulkan/Buffers/VkBuffer.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	void Cubemap::Create(const Device& _device, CommandBuffer& _cmd, ResourceHolder& _resHold, const RawCubemap& _raw)
	{
		//uint64 dataSize = _raw.GetTotalMapSize();
		//uint64 irradianceSize = _raw.GetMapSize();

		//Buffer& stagingBuffer = _resHold.Make<Buffer>(Buffer::Deleter(_device));
		//stagingBuffer.Create(_device, dataSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		//	VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		//	_raw.data.data());


		//ImageBufferCreateInfos imageBufferCreateInfos;

		//imageBufferCreateInfos.imageType = ImageType::Cube;

		//imageBufferCreateInfos.format = _raw.format;
		//imageBufferCreateInfos.extent = _raw.extent;

		//imageBufferCreateInfos.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
		//imageBufferCreateInfos.mipLevels = _raw.mipLevels;

		//if (_raw.mipLevels > 1)
		//	imageBufferCreateInfos.usage |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;

		//
		//// === Create buffer ===
		//mBuffer.Create(_device, imageBufferCreateInfos);

		//// Copy image to shader.
		//ImageBuffer::TransitionInfos undefToDstTransitionInfos{};
		//undefToDstTransitionInfos.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		//undefToDstTransitionInfos.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		//undefToDstTransitionInfos.mipLevels = _raw.mipLevels;
		//undefToDstTransitionInfos.imageType = ImageType::Cube;

		//mBuffer.TransitionImageLayout(_cmd, _resHold, undefToDstTransitionInfos);


		//ImageBuffer::CopyBufferImageInfos copyInfos{};
		//copyInfos.buffer = stagingBuffer;
		//copyInfos.extent = _raw.extent;
		//copyInfos.format = _raw.format;
		//copyInfos.mipLevels = _raw.mipLevels;
		//copyInfos.imageType = ImageType::Cube;

		//mBuffer.CopyBufferToImage(_cmd, _resHold, copyInfos);


		//ImageBuffer::TransitionInfos dstToReadTransitionInfos{};
		//dstToReadTransitionInfos.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		//dstToReadTransitionInfos.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		//dstToReadTransitionInfos.mipLevels = _raw.mipLevels;
		//dstToReadTransitionInfos.imageType = ImageType::Cube;

		//mBuffer.TransitionImageLayout(_cmd, _resHold, dstToReadTransitionInfos);


		//// Destroy will be called by ResourceHolder.
		////stagingBuffer.Destroy(device);


		//// === Create irradiance buffer ===
		//Buffer& irrStagingBuffer = _resHold.Make<Buffer>(Buffer::Deleter(_device));
		//irrStagingBuffer.Create(_device, irradianceSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		//	VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		//	_raw.data.data());

		//imageBufferCreateInfos.mipLevels = 1u;
		//imageBufferCreateInfos.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

		//copyInfos.mipLevels = 1u;
		//copyInfos.buffer = irrStagingBuffer;
		//undefToDstTransitionInfos.mipLevels = 1u;
		//dstToReadTransitionInfos.mipLevels = 1u;


		//mIrradianceBuffer.Create(_device, imageBufferCreateInfos);

		//mIrradianceBuffer.TransitionImageLayout(_cmd, _resHold, undefToDstTransitionInfos);

		//mIrradianceBuffer.CopyBufferToImage(_cmd, _resHold, copyInfos);

		//mIrradianceBuffer.TransitionImageLayout(_cmd, _resHold, dstToReadTransitionInfos);


		// Destroy will be called by ResourceHolder.
		//irrStagingBuffer.Destroy(device);


		mSampler.Create(_device, _raw.mipLevels);
	}

	void Cubemap::Destroy(const Device& _device)
	{
		mSampler.Destroy(_device);

		mBuffer.Destroy(_device);
		mIrradianceBuffer.Destroy(_device);
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

#endif
