// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Material/VkDescriptorPool.hpp>

#include <Render/Base/Pipeline/Descriptors/PipelineBindingSetDescriptor.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>

namespace SA::VK
{
	void DescriptorPoolInfos::AddBindings(const PipelineBindingSetDescriptor& _desc)
	{
		for (auto it = _desc.bindings.begin(); it != _desc.bindings.end(); ++it)
		{
			/**
			*	Multiple pool size descriptor with same type is fine: total will be calculated.
			*	Source: https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkDescriptorPoolCreateInfo.html
			*/

			VkDescriptorPoolSize& poolSize = poolSizes.emplace_back();
			poolSize.type = API_GetDescriptorType(it->type);
			poolSize.descriptorCount = 1u;
		}
	}


	void DescriptorPool::Create(const Device& _device, const DescriptorPoolInfos& _infos)
	{
		VkDescriptorPoolCreateInfo descriptorPoolInfo{};
		descriptorPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		descriptorPoolInfo.pNext = nullptr;
		descriptorPoolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
		descriptorPoolInfo.maxSets = _infos.setNum;
		descriptorPoolInfo.poolSizeCount = (uint32_t)(_infos.poolSizes.size());
		descriptorPoolInfo.pPoolSizes = _infos.poolSizes.data();

		SA_VK_ASSERT(vkCreateDescriptorPool(_device, &descriptorPoolInfo, nullptr, &mHandle),
			L"Failed to create descriptor pool!");
	}
	
	void DescriptorPool::Destroy(const Device& _device)
	{
		vkDestroyDescriptorPool(_device, mHandle, nullptr);
		mHandle = VK_NULL_HANDLE;
	}


	DescriptorSet DescriptorPool::Allocate(const Device& _device, const DescriptorSetLayout& _layout)
	{
		DescriptorSet set = VK_NULL_HANDLE;

		VkDescriptorSetAllocateInfo descriptorSetAllocInfo{};
		descriptorSetAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		descriptorSetAllocInfo.pNext = nullptr;
		descriptorSetAllocInfo.descriptorPool = mHandle;
		descriptorSetAllocInfo.descriptorSetCount = 1u;
		descriptorSetAllocInfo.pSetLayouts = reinterpret_cast<const VkDescriptorSetLayout*>(&_layout);

		SA_VK_ASSERT(vkAllocateDescriptorSets(_device, &descriptorSetAllocInfo, &set), L"Failed to allocate descriptor set!");

		return set;
	}
	
	std::vector<DescriptorSet> DescriptorPool::Allocate(const Device& _device, const std::vector<DescriptorSetLayout>& _layouts)
	{
		const uint32_t num = _layouts.size();

		std::vector<DescriptorSet> sets(num, VK_NULL_HANDLE);

		VkDescriptorSetAllocateInfo descriptorSetAllocInfo{};
		descriptorSetAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		descriptorSetAllocInfo.pNext = nullptr;
		descriptorSetAllocInfo.descriptorPool = mHandle;
		descriptorSetAllocInfo.descriptorSetCount = num;
		descriptorSetAllocInfo.pSetLayouts = reinterpret_cast<const VkDescriptorSetLayout*>(_layouts.data());

		SA_VK_ASSERT(vkAllocateDescriptorSets(_device, &descriptorSetAllocInfo, sets.data()), L"Failed to allocate descriptor set!");

		return sets;
	}

	
	void DescriptorPool::Free(const Device& _device, DescriptorSet& _set)
	{
		vkFreeDescriptorSets(_device, mHandle, 1u, &_set);
	}
	
	void DescriptorPool::Free(const Device& _device, std::vector<DescriptorSet>& _sets)
	{
		vkFreeDescriptorSets(_device, mHandle, (uint32_t)_sets.size(), _sets.data());
	}


	DescriptorPool::operator VkDescriptorPool() const noexcept
	{
		return mHandle;
	}
}
