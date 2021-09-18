// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Material/VkMaterial.hpp>

#include <Core/Algorithms/SizeOf.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>
#include <Render/Vulkan/Pipeline/VkPipeline.hpp>
#include <Render/Vulkan/VkRenderFrame.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	void Material::Create(const Device& _device, const MaterialCreateInfos& _infos)
	{
		CreateDescriptorPool(_device, _infos);
		CreateDescriptorSets(_device, _infos);
	}

	void Material::Destroy(const Device& _device)
	{
		DestroyDescriptorSets(_device);
		DestroyDescriptorPool(_device);
	}

	void Material::Bind(const ARenderFrame& _frame, const APipeline& _pipeline) const
	{
		const RenderFrame& vkFrame = _frame.As<RenderFrame>();
		const Pipeline& vkPipeline = _pipeline.As<Pipeline>();

		// TODO: Add frame index.
		vkCmdBindDescriptorSets(vkFrame.cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, vkPipeline.GetLayout(),
			0, 1, /*&mDescriptorSets[_frame.index % SizeOf(mDescriptorSets)]*/ &mDescriptorSets[0], 0, nullptr);
	}


	void Material::CreateDescriptorPool(const Device& _device, const MaterialCreateInfos& _infos)
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

	void Material::DestroyDescriptorPool(const Device& _device)
	{
		vkDestroyDescriptorPool(_device, mDescriptorPool, nullptr);
		mDescriptorPool = VK_NULL_HANDLE;
	}


	void Material::CreateDescriptorSets(const Device& _device, const MaterialCreateInfos& _infos)
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
		
		UpdateDescriptorSets(_device, _infos.bindings);
	}


	void Material::UpdateDescriptorSets(const Device& _device, const std::vector<AMaterialBinding*>& _bindings)
	{
		std::list<std::vector<VkDescriptorBufferInfo>> bufferDescs;
		std::list<std::vector<VkDescriptorImageInfo>> imageDescs;
		std::vector<VkWriteDescriptorSet> descWrites;


		for (auto it = _bindings.cbegin(); it != _bindings.cend(); ++it)
		{
			const AMaterialBinding& bind = **it;

			VkWriteDescriptorSet descWrite = bind.MakeVkDescriptors(bufferDescs, imageDescs);

			// Update for all descriptors.
			if (bind.descriptor == ~uint32())
			{
				for (uint32 i = 0u; i < SizeOf(mDescriptorSets); ++i)
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

	void Material::DestroyDescriptorSets(const Device& _device)
	{
		(void)_device;

		// Not needed when vkDestroyDescriptorPool() is called. Otherwise, requiere VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT flag.
		//vkFreeDescriptorSets(_device, mDescriptorPool, SizeOf<uint32>(mDescriptorSets), mDescriptorSets.data());
		mDescriptorSets.clear();
	}
}

#endif
