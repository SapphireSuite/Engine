// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Pipeline/DescriptorSet/VkDescriptorPool.hpp>

#include <Core/Algorithms/SizeOf.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>
#include <Render/Vulkan/Pipeline/DescriptorSet/VkDescriptorSetLayout.hpp>

namespace Sa::Vk
{
	void DescriptorPool::Create(const Device& _device, const PipelineBindingSetDescriptor& _bindSetDesc, uint32 _maxSet)
	{
		std::vector<VkDescriptorPoolSize> poolSizes;

		for (auto& bind : _bindSetDesc.bindings)
		{
			/**
			*	Multiple pool size descriptor with same type is fine: total will be calculated.
			*	Source: https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkDescriptorPoolCreateInfo.html
			*/

			VkDescriptorPoolSize& poolSize = poolSizes.emplace_back();
			poolSize.type = API_GetDescriptorType(bind.type);
			poolSize.descriptorCount = bind.num;
		}


		VkDescriptorPoolCreateInfo descriptorPoolInfo{};
		descriptorPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		descriptorPoolInfo.pNext = nullptr;
		descriptorPoolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
		descriptorPoolInfo.maxSets = _maxSet;
		descriptorPoolInfo.poolSizeCount = SizeOf<uint32>(poolSizes);
		descriptorPoolInfo.pPoolSizes = poolSizes.data();

		SA_VK_ASSERT(vkCreateDescriptorPool(_device, &descriptorPoolInfo, nullptr, &mHandle), L"Failed to create descriptor pool!");
	}
	
	void DescriptorPool::Destroy(const Device& _device)
	{
		vkDestroyDescriptorPool(_device, mHandle, nullptr);
		mHandle = VK_NULL_HANDLE;
	}


	DescriptorSet DescriptorPool::Allocate(const Device& _device, const DescriptorSetLayout& _layout)
	{
		VkDescriptorSetAllocateInfo descriptorSetAllocInfo{};
		descriptorSetAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		descriptorSetAllocInfo.pNext = nullptr;
		descriptorSetAllocInfo.descriptorPool = mHandle;
		descriptorSetAllocInfo.descriptorSetCount = 1u;
		descriptorSetAllocInfo.pSetLayouts = &_layout.GetHandle();

		DescriptorSet descSet;

		SA_VK_ASSERT(vkAllocateDescriptorSets(_device, &descriptorSetAllocInfo, &descSet.mHandle), L"Failed to allocate descriptor set!");

		return descSet;
	}

	std::vector<DescriptorSet> DescriptorPool::Allocate(const Device& _device, const std::vector<DescriptorSetLayout>& _layouts)
	{
		VkDescriptorSetAllocateInfo descriptorSetAllocInfo{};
		descriptorSetAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		descriptorSetAllocInfo.pNext = nullptr;
		descriptorSetAllocInfo.descriptorPool = mHandle;
		descriptorSetAllocInfo.descriptorSetCount = SizeOf<uint32>(_layouts);

		static_assert(sizeof(DescriptorSetLayout) == sizeof(VkDescriptorSetLayout), "Size doesn't match: Invalid reinterpret_cast!");
		descriptorSetAllocInfo.pSetLayouts = reinterpret_cast<const VkDescriptorSetLayout*>(_layouts.data());

		std::vector<DescriptorSet> descSets(SizeOf<uint32>(_layouts));

		static_assert(sizeof(VkDescriptorSet) == sizeof(VkDescriptorSet), "Size doesn't match: Invalid reinterpret_cast!");
		VkDescriptorSet* const vkDescSets = reinterpret_cast<VkDescriptorSet*>(descSets.data());

		SA_VK_ASSERT(vkAllocateDescriptorSets(_device, &descriptorSetAllocInfo, vkDescSets), L"Failed to allocate descriptor set!");

		return descSets;
	}


	void DescriptorPool::Free(const Device& _device, DescriptorSet& _descSet)
	{
		vkFreeDescriptorSets(_device, mHandle, 1u, &_descSet.mHandle);
		_descSet.mHandle = VK_NULL_HANDLE;
	}

	void DescriptorPool::Free(const Device& _device, std::vector<DescriptorSet>& _descSets)
	{
		static_assert(sizeof(VkDescriptorSet) == sizeof(VkDescriptorSet), "Size doesn't match: Invalid reinterpret_cast!");
		vkFreeDescriptorSets(_device, mHandle, 1u, reinterpret_cast<VkDescriptorSet*>(_descSets.data()));
		
		for(auto& descSet : _descSets)
			descSet.mHandle = VK_NULL_HANDLE;
	}


	DescriptorPool::operator VkDescriptorPool() const noexcept
	{
		return mHandle;
	}
}
