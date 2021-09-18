// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Pipeline/DescriptorSets/VkDescriptorMultiSet.hpp>

#include <Core/Algorithms/SizeOf.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>
#include <Render/Vulkan/Pipeline/VkPipeline.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	void DescriptorMultiSet::CreateDescriptorSets(const Device& _device, const DescriptorSetCreateInfos& _infos)
	{
		const Pipeline& vkPipeline = _infos.pipeline.As<Pipeline>();

		mDescriptorSets.resize(_infos.descriptorSetNum);
		std::vector<VkDescriptorSetLayout> descriptorSetLayouts(_infos.descriptorSetNum, vkPipeline.GetDescriptorSetLayout());

		VkDescriptorSetAllocateInfo descriptorSetAllocInfo{};
		descriptorSetAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		descriptorSetAllocInfo.pNext = nullptr;
		descriptorSetAllocInfo.descriptorPool = mDescriptorPool;
		descriptorSetAllocInfo.descriptorSetCount = _infos.descriptorSetNum;
		descriptorSetAllocInfo.pSetLayouts = descriptorSetLayouts.data();

		SA_VK_ASSERT(vkAllocateDescriptorSets(_device, &descriptorSetAllocInfo, mDescriptorSets.data()), L"Failed to allocate descriptor sets!");
	}

	void DescriptorMultiSet::UpdateDescriptorSets(const Device& _device, const std::vector<AShaderBinding*>& _bindings)
	{
		std::list<std::vector<VkDescriptorBufferInfo>> bufferDescs;
		std::list<std::vector<VkDescriptorImageInfo>> imageDescs;
		std::vector<VkWriteDescriptorSet> descWrites;


		for (auto it = _bindings.cbegin(); it != _bindings.cend(); ++it)
		{
			const AShaderBinding& bind = **it;

			VkWriteDescriptorSet descWrite = bind.MakeVkDescriptors(bufferDescs, imageDescs);

			// Update for all descriptors.
			if (bind.descriptor == ~uint32())
			{
				for (uint32 i = 0u; i < SizeOf<uint32>(mDescriptorSets); ++i)
				{
					descWrite.dstSet = mDescriptorSets[i];
					descWrites.push_back(descWrite);
				}
			}
			else
			{
				SA_ASSERT(OutOfRange, SA/Render/Vulkan, bind.descriptor, 0u, SizeOf<uint32>(mDescriptorSets), L"Invalid descriptor set index!");

				descWrite.dstSet = mDescriptorSets[bind.descriptor];
				descWrites.push_back(descWrite);
			}
		}

		vkUpdateDescriptorSets(_device, SizeOf<uint32>(descWrites), descWrites.data(), 0, nullptr);
	}

	void DescriptorMultiSet::DestroyDescriptorSets(const Device& _device)
	{
		(void)_device;

		// Not needed when vkDestroyDescriptorPool() is called. Otherwise, requiere VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT flag.
		//vkFreeDescriptorSets(_device, mDescriptorPool, SizeOf<uint32>(mDescriptorSets), mDescriptorSets.data());
		mDescriptorSets.clear();
	}
}

#endif
