// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Pipeline/VkDescriptorSet.hpp>

#include <Core/Algorithms/SizeOf.hpp>

#include <Render/Base/Material/Bindings/ARenderMaterialBinding.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>
#include <Render/Vulkan/Pipeline/VkPipeline.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	void DescriptorSet::Create(const Device& _device, const PipelineBindingSetDescriptor& _infos, VkDescriptorSetLayout _descSetLayout)
	{
		CreateDescriptorPool(_device, _infos);

		CreateDescriptorSet(_device, _descSetLayout);
	}

	void DescriptorSet::Destroy(const Device& _device)
	{
		DestroyDescriptorSet(_device);
		DestroyDescriptorPool(_device);
	}


	void DescriptorSet::Update(const Device& _device, const std::vector<const ARenderMaterialBinding*>& _bindings)
	{
		std::list<std::vector<VkDescriptorBufferInfo>> bufferDescs;
		std::list<std::vector<VkDescriptorImageInfo>> imageDescs;
		std::vector<VkWriteDescriptorSet> descWrites;


		for (auto it = _bindings.cbegin(); it != _bindings.cend(); ++it)
		{
			const ARenderMaterialBinding& bind = **it;

			VkWriteDescriptorSet descWrite = bind.MakeVkDescriptors(bufferDescs, imageDescs);
			descWrite.dstSet = mHandle;

			descWrites.push_back(descWrite);
		}

		vkUpdateDescriptorSets(_device, SizeOf<uint32>(descWrites), descWrites.data(), 0, nullptr);
	}


	void DescriptorSet::CreateDescriptorPool(const Device& _device, const PipelineBindingSetDescriptor& _infos)
	{
		std::vector<VkDescriptorPoolSize> poolSizes;

		for (auto it = _infos.bindings.begin(); it != _infos.bindings.end(); ++it)
		{
			/**
			*	Multiple pool size descriptor with same type is fine: total will be calculated.
			*	Source: https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkDescriptorPoolCreateInfo.html
			*/

			VkDescriptorPoolSize& poolSize = poolSizes.emplace_back();
			poolSize.type = API_GetDescriptorType(it->type);
			poolSize.descriptorCount = 1u;
		}


		VkDescriptorPoolCreateInfo descriptorPoolInfo{};
		descriptorPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		descriptorPoolInfo.pNext = nullptr;
		descriptorPoolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
		descriptorPoolInfo.maxSets = 1u;
		descriptorPoolInfo.poolSizeCount = SizeOf<uint32>(poolSizes);
		descriptorPoolInfo.pPoolSizes = poolSizes.data();

		SA_VK_ASSERT(vkCreateDescriptorPool(_device, &descriptorPoolInfo, nullptr, &mDescriptorPool), L"Failed to create descriptor pool!");
	}

	void DescriptorSet::DestroyDescriptorPool(const Device& _device)
	{
		vkDestroyDescriptorPool(_device, mDescriptorPool, nullptr);
		mDescriptorPool = VK_NULL_HANDLE;
	}


	void DescriptorSet::CreateDescriptorSet(const Device& _device, VkDescriptorSetLayout _descSetLayout)
	{
		VkDescriptorSetAllocateInfo descriptorSetAllocInfo{};
		descriptorSetAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		descriptorSetAllocInfo.pNext = nullptr;
		descriptorSetAllocInfo.descriptorPool = mDescriptorPool;
		descriptorSetAllocInfo.descriptorSetCount = 1u;
		descriptorSetAllocInfo.pSetLayouts = &_descSetLayout;

		SA_VK_ASSERT(vkAllocateDescriptorSets(_device, &descriptorSetAllocInfo, &mHandle), L"Failed to allocate descriptor set!");
	}

	void DescriptorSet::DestroyDescriptorSet(const Device& _device)
	{
		(void)_device;

		// Not needed when vkDestroyDescriptorPool() is called. Otherwise, requiere VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT flag.
		//vkFreeDescriptorSets(_device, mDescriptorPool, 1u, mDescriptorSets);
	}
}

#endif
