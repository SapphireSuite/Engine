// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Pipeline/DescriptorSet/VkDescriptorSetLayout.hpp>

#include <Core/Algorithms/SizeOf.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>

namespace Sa::Vk
{
	const VkDescriptorSetLayout& DescriptorSetLayout::GetHandle() const noexcept
	{
		return mHandle;
	}


	void DescriptorSetLayout::Create(const Device& _device, const PipelineBindingSetDescriptor& _pipBindSetDesc)
	{
		std::vector<VkDescriptorSetLayoutBinding> descSetLayout;
		descSetLayout.reserve(_pipBindSetDesc.bindings.size());

		for (auto& bind : _pipBindSetDesc.bindings)
		{
			VkDescriptorSetLayoutBinding& descBinding = descSetLayout.emplace_back();

			descBinding.binding = bind.binding;
			descBinding.descriptorType = API_GetDescriptorType(bind.type);
			descBinding.descriptorCount = bind.num;
			descBinding.stageFlags = API_GetShaderStageFlags(bind.stageFlags);
			descBinding.pImmutableSamplers = nullptr;
		}

		VkDescriptorSetLayoutCreateInfo descriptorSetLayoutInfo{};
		descriptorSetLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		descriptorSetLayoutInfo.pNext = nullptr;
		descriptorSetLayoutInfo.flags = 0u;
		descriptorSetLayoutInfo.bindingCount = SizeOf<uint32>(descSetLayout);
		descriptorSetLayoutInfo.pBindings = descSetLayout.data();

		SA_VK_ASSERT(vkCreateDescriptorSetLayout(_device, &descriptorSetLayoutInfo, nullptr, &mHandle),
			L"Failed to create descriptor set layout!");
	}

	void DescriptorSetLayout::Destroy(const Device& _device)
	{
		vkDestroyDescriptorSetLayout(_device, mHandle, nullptr);
		mHandle = VK_NULL_HANDLE;
	}


	DescriptorSetLayout::operator VkDescriptorSetLayout() const noexcept
	{
		return mHandle;
	}
}
