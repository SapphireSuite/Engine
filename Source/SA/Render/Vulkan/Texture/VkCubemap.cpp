// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Texture/VkCubemap.hpp>

#include <Render/Vulkan/VkResourceInitializer.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>
#include <Render/Vulkan/Buffers/VkBuffer.hpp>

namespace Sa::Vk
{
	void Cubemap::Create(const Device& _device, ResourceInitializer& _init, const RawCubemap& _raw)
	{
		Texture::Create(_device, _init, _raw);


		Buffer& irrStagingBuffer = Buffer::CreateStaging(_device, _init, _raw.irradiancemapData.data(), _raw.GetMapSize());


		// Create Device Image buffer
		{
			ImageBufferCreateInfos imageBufferCreateInfos;

			imageBufferCreateInfos.imageType = ImageType::Cube;

			imageBufferCreateInfos.format = _raw.format;
			imageBufferCreateInfos.extent = _raw.extent;

			imageBufferCreateInfos.mipLevels = 1u;
			imageBufferCreateInfos.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

			mIrradianceBuffer.Create(_device, imageBufferCreateInfos);
		}


		// Undef to Dst Transition
		{
			ImageBuffer::TransitionInfos undefToDstTransitionInfos{};
			undefToDstTransitionInfos.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			undefToDstTransitionInfos.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
			undefToDstTransitionInfos.mipLevels = 1u;
			undefToDstTransitionInfos.imageType = ImageType::Cube;

			mIrradianceBuffer.TransitionImageLayout(_init, undefToDstTransitionInfos);
		}


		// Copy staging to device
		{
			ImageBuffer::CopyBufferImageInfos copyInfos{};
			copyInfos.buffer = irrStagingBuffer;
			copyInfos.extent = _raw.extent;
			copyInfos.format = _raw.format;
			copyInfos.mipLevels = 1u;
			copyInfos.imageType = ImageType::Cube;

			mIrradianceBuffer.CopyBufferToImage(_init, copyInfos);
		}


		// Dst to Read Transition
		{
			ImageBuffer::TransitionInfos dstToReadTransitionInfos{};
			dstToReadTransitionInfos.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
			dstToReadTransitionInfos.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			dstToReadTransitionInfos.mipLevels = 1u;
			dstToReadTransitionInfos.imageType = ImageType::Cube;

			mIrradianceBuffer.TransitionImageLayout(_init, dstToReadTransitionInfos);
		}


		// Destroy will be called by ResourceHolder.
		//irrStagingBuffer.Destroy(device);

		SA_LOG(L"Cubemap created.", Infos, SA/Render/Vulkan);
	}

	void Cubemap::Destroy(const Device& _device)
	{
		Texture::Destroy(_device);
		
		mIrradianceBuffer.Destroy(_device);
		
		SA_LOG(L"Cubemap destroyed.", Infos, SA/Render/Vulkan);
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


	bool Cubemap::operator==(const Cubemap& _rhs) const noexcept
	{
		return Texture::operator==(_rhs) && mIrradianceBuffer == _rhs.mIrradianceBuffer;
	}
}
