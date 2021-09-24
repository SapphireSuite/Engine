// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Pipeline/VkDescriptorSet.hpp>

#include <set>

#include <Core/Algorithms/SizeOf.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/VkFrame.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>
#include <Render/Vulkan/Pipeline/VkPipeline.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	void DescriptorSet::Create(const Device& _device, const DescriptorSetCreateInfos& _infos)
	{
		CreateDescriptorPool(_device, _infos);

		CreateDescriptorSets(_device, _infos);
		UpdateDescriptorSets(_device, _infos.bindings);
	}

	void DescriptorSet::Destroy(const Device& _device)
	{
		DestroyDescriptorSets(_device);
		DestroyDescriptorPool(_device);
	}


	void DescriptorSet::CreateDescriptorPool(const Device& _device, const DescriptorSetCreateInfos& _infos)
	{
		const Pipeline& vkPipeline = _infos.pipeline.As<Vk::Pipeline>();

		std::vector<VkDescriptorPoolSize> poolSizes;

		for (auto it = _infos.bindings.begin(); it != _infos.bindings.end(); ++it)
		{
			/**
			*	Multiple pool size descriptor with same type is fine: total will be calculated.
			*	Source: https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkDescriptorPoolCreateInfo.html
			*/

			VkDescriptorPoolSize& poolSize = poolSizes.emplace_back();
			poolSize.type = (*it)->GetVkDescriptorType();
			poolSize.descriptorCount = 1u;
		}


		VkDescriptorPoolCreateInfo descriptorPoolInfo{};
		descriptorPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		descriptorPoolInfo.pNext = nullptr;
		descriptorPoolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
		descriptorPoolInfo.maxSets = SizeOf<uint32>(vkPipeline.GetDescriptorSetLayouts());
		descriptorPoolInfo.poolSizeCount = SizeOf<uint32>(poolSizes);
		descriptorPoolInfo.pPoolSizes = poolSizes.data();

		SA_VK_ASSERT(vkCreateDescriptorPool(_device, &descriptorPoolInfo, nullptr, &mDescriptorPool), L"Failed to create descriptor pool!");
	}

	void DescriptorSet::DestroyDescriptorPool(const Device& _device)
	{
		vkDestroyDescriptorPool(_device, mDescriptorPool, nullptr);
		mDescriptorPool = VK_NULL_HANDLE;
	}


	void DescriptorSet::CreateDescriptorSets(const Device& _device, const DescriptorSetCreateInfos& _infos)
	{
		const Pipeline& vkPipeline = _infos.pipeline.As<Pipeline>();
		const std::vector<VkDescriptorSetLayout>& descriptorSetLayouts = vkPipeline.GetDescriptorSetLayouts();

		mDescriptorSets.resize(descriptorSetLayouts.size());

		VkDescriptorSetAllocateInfo descriptorSetAllocInfo{};
		descriptorSetAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		descriptorSetAllocInfo.pNext = nullptr;
		descriptorSetAllocInfo.descriptorPool = mDescriptorPool;
		descriptorSetAllocInfo.descriptorSetCount = SizeOf<uint32>(descriptorSetLayouts);
		descriptorSetAllocInfo.pSetLayouts = descriptorSetLayouts.data();

		SA_VK_ASSERT(vkAllocateDescriptorSets(_device, &descriptorSetAllocInfo, mDescriptorSets.data()), L"Failed to allocate descriptor set!");
	}

	void DescriptorSet::UpdateDescriptorSets(const Device& _device, const std::vector<AShaderBinding*>& _bindings)
	{
		std::list<std::vector<VkDescriptorBufferInfo>> bufferDescs;
		std::list<std::vector<VkDescriptorImageInfo>> imageDescs;
		std::vector<VkWriteDescriptorSet> descWrites;


		for (auto it = _bindings.cbegin(); it != _bindings.cend(); ++it)
		{
			const AShaderBinding& bind = **it;

			VkWriteDescriptorSet descWrite = bind.MakeVkDescriptors(bufferDescs, imageDescs);
			descWrite.dstSet = mDescriptorSets[bind.set];

			descWrites.push_back(descWrite);
		}

		vkUpdateDescriptorSets(_device, SizeOf<uint32>(descWrites), descWrites.data(), 0, nullptr);
	}

	void DescriptorSet::DestroyDescriptorSets(const Device& _device)
	{
		(void)_device;

		// Not needed when vkDestroyDescriptorPool() is called. Otherwise, requiere VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT flag.
		//vkFreeDescriptorSets(_device, mDescriptorPool, SizeOf<uint32>(mDescriptorSets), mDescriptorSets.data());
		mDescriptorSets.clear();
	}


	void DescriptorSet::Bind(const ARenderFrame& _frame, const ARenderPipeline& _pipeline) const
	{
		const Frame& vkFrame = _frame.As<Frame>();
		const Pipeline& vkPipeline = _pipeline.As<Pipeline>();

		vkCmdBindDescriptorSets(vkFrame.cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, vkPipeline.GetLayout(),
			0u, SizeOf<uint32>(mDescriptorSets), mDescriptorSets.data(), 0, nullptr);
	}
}

#endif
