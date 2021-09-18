// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Pipeline/DescriptorSets/VkDescriptorSetBase.hpp>

#include <Core/Algorithms/SizeOf.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	void DescriptorSetBase::Create(const Device& _device, const DescriptorSetCreateInfos& _infos)
	{
		CreateDescriptorPool(_device, _infos);

		CreateDescriptorSets(_device, _infos);
		UpdateDescriptorSets(_device, _infos.bindings);
	}

	void DescriptorSetBase::Destroy(const Device& _device)
	{
		DestroyDescriptorSets(_device);
		DestroyDescriptorPool(_device);
	}

	
	void DescriptorSetBase::CreateDescriptorPool(const Device& _device, const DescriptorSetCreateInfos& _infos)
	{
		std::unordered_map<VkDescriptorType, uint32> poolMap;

		// Count each bindings with type.
		for (auto it = _infos.bindings.begin(); it != _infos.bindings.end(); ++it)
			++poolMap[(*it)->GetVkDescriptorType()];


		// Merge into vector.
		std::vector<VkDescriptorPoolSize> poolSizes;
		poolSizes.reserve(poolMap.size());

		for (auto it = poolMap.begin(); it != poolMap.end(); ++it)
		{
			VkDescriptorPoolSize& poolSize = poolSizes.emplace_back();

			poolSize.type = it->first;
			poolSize.descriptorCount = it->second;
		}


		VkDescriptorPoolCreateInfo descriptorPoolInfo{};
		descriptorPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		descriptorPoolInfo.pNext = nullptr;
		descriptorPoolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
		descriptorPoolInfo.maxSets = _infos.descriptorSetNum;
		descriptorPoolInfo.poolSizeCount = SizeOf<uint32>(poolSizes);
		descriptorPoolInfo.pPoolSizes = poolSizes.data();

		SA_VK_ASSERT(vkCreateDescriptorPool(_device, &descriptorPoolInfo, nullptr, &mDescriptorPool), L"Failed to create descriptor pool!");
	}

	void DescriptorSetBase::DestroyDescriptorPool(const Device& _device)
	{
		vkDestroyDescriptorPool(_device, mDescriptorPool, nullptr);
		mDescriptorPool = VK_NULL_HANDLE;
	}
}

#endif
