// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Material/VkDescriptorSetLayout.hpp>

#include <Render/Base/Pipeline/Descriptors/PipelineBindingSetDescriptor.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>

namespace SA::VK
{
	void DescriptorSetLayout::Create(const Device& _device, const PipelineBindingSetDescriptor& _desc)
	{
		std::vector<VkDescriptorSetLayoutBinding> descSetLayout;

		for (auto& bind : _desc.bindings)
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
		descriptorSetLayoutInfo.bindingCount = 1u;
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
