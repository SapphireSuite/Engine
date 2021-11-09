// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Pipeline/DescriptorSet/VkDescriptorSet.hpp>

#include <Core/Algorithms/SizeOf.hpp>

#include <Render/Vulkan/Device/VkDevice.hpp>
#include <Render/Vulkan/Buffers/VkBuffer.hpp>
#include <Render/Vulkan/Texture/VkTexture.hpp>

namespace Sa::Vk
{
//{ Update

	DescriptorSet::Updater::Updater(const DescriptorSet& _handle) :
		mDescriptorSet { _handle }
	{
	}


	VkWriteDescriptorSet DescriptorSet::Updater::MakeDefaultWriteDescriptors(uint32 _binding)
	{
		VkWriteDescriptorSet descWrite{};
		descWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descWrite.pNext = nullptr;

		descWrite.dstSet = mDescriptorSet;
		descWrite.dstBinding = _binding;

		return descWrite;
	}


	void DescriptorSet::Updater::Add(uint32 _binding, const std::vector<const Buffer*>& _buffers)
	{
		std::vector<VkDescriptorBufferInfo>& descs = mBufferDescs.emplace_back();
		descs.reserve(_buffers.size());

		for (auto buffer : _buffers)
			descs.push_back(buffer->CreateDescriptorBufferInfo());

		VkWriteDescriptorSet& descWrite = mDescWrites.emplace_back(MakeDefaultWriteDescriptors(_binding));
		descWrite.descriptorCount = SizeOf<uint32>(descs);
		descWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descWrite.pBufferInfo = descs.data();
	}

	void DescriptorSet::Updater::Add(uint32 _binding, const std::vector<const Texture*>& _textures)
	{
		std::vector<VkDescriptorImageInfo>& descs = mImageDescs.emplace_back();
		descs.reserve(_textures.size());

		for (auto texture : _textures)
			descs.push_back(texture->CreateDescriptorImageInfo());

		VkWriteDescriptorSet& descWrite = mDescWrites.emplace_back(MakeDefaultWriteDescriptors(_binding));
		descWrite.descriptorCount = SizeOf<uint32>(descs);
		descWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		descWrite.pImageInfo = descs.data();
	}


	void DescriptorSet::Updater::Submit(const Device& _device) const
	{
		vkUpdateDescriptorSets(_device, SizeOf<uint32>(mDescWrites), mDescWrites.data(), 0, nullptr);
	}


	DescriptorSet::Updater DescriptorSet::MakeUpdater()
	{
		return Updater(*this);
	}

//}


	DescriptorSet::operator VkDescriptorSet() const noexcept
	{
		return mHandle;
	}
}
