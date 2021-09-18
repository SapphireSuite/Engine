// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Pipeline/DescriptorSets/VkDescriptorSet.hpp>

#include <Core/Algorithms/SizeOf.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>
#include <Render/Vulkan/Pipeline/VkPipeline.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	void DescriptorSet::CreateDescriptorSets(const Device& _device, const DescriptorSetCreateInfos& _infos)
	{
		const Pipeline& vkPipeline = _infos.pipeline.As<Pipeline>();

		VkDescriptorSetLayout descriptorSetLayout = vkPipeline.GetDescriptorSetLayout();

		VkDescriptorSetAllocateInfo descriptorSetAllocInfo{};
		descriptorSetAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		descriptorSetAllocInfo.pNext = nullptr;
		descriptorSetAllocInfo.descriptorPool = mDescriptorPool;
		descriptorSetAllocInfo.descriptorSetCount = 1u;
		descriptorSetAllocInfo.pSetLayouts = &descriptorSetLayout;

		SA_VK_ASSERT(vkAllocateDescriptorSets(_device, &descriptorSetAllocInfo, &mDescriptorSet), L"Failed to allocate descriptor set!");
	}

	void DescriptorSet::UpdateDescriptorSets(const Device& _device, const std::vector<AShaderBinding*>& _bindings)
	{
		std::list<std::vector<VkDescriptorBufferInfo>> bufferDescs;
		std::list<std::vector<VkDescriptorImageInfo>> imageDescs;
		std::vector<VkWriteDescriptorSet> descWrites;


		for (auto it = _bindings.cbegin(); it != _bindings.cend(); ++it)
		{
			const AShaderBinding& bind = **it;

			SA_WARN(bind.descriptor == ~uint32(), SA/Render/Vulkan, L"Shader binding with specified descriptor number ignored");


			VkWriteDescriptorSet descWrite = bind.MakeVkDescriptors(bufferDescs, imageDescs);
			descWrite.dstSet = mDescriptorSet;

			descWrites.push_back(descWrite);
		}

		vkUpdateDescriptorSets(_device, SizeOf<uint32>(descWrites), descWrites.data(), 0, nullptr);
	}

	void DescriptorSet::DestroyDescriptorSets(const Device& _device)
	{
		(void)_device;

		// Not needed when vkDestroyDescriptorPool() is called. Otherwise, requiere VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT flag.
		//vkFreeDescriptorSets(_device, mDescriptorPool, 1, &mDescriptorSet);
		mDescriptorSet = VK_NULL_HANDLE;
	}
}

#endif
