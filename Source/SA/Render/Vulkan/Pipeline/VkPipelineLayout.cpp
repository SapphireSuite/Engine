// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Pipeline/VkPipelineLayout.hpp>

#include <Core/Algorithms/SizeOf.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>
#include <Render/Vulkan/Pipeline/DescriptorSet/VkDescriptorSetLayout.hpp>

namespace Sa::Vk
{
	std::vector<VkDescriptorSetLayout> ToVkDescriptorSetLayouts(const std::vector<DescriptorSetLayout>& _descSetLayouts)
	{
		std::vector<VkDescriptorSetLayout> vkLayouts;
		vkLayouts.reserve(_descSetLayouts.size());

		for (auto& descLayout : _descSetLayouts)
			vkLayouts.emplace_back(descLayout);

		return vkLayouts;
	}

	std::vector<VkPushConstantRange> FillPushConstantRanges(const std::vector<PipelinePushConstantDescriptor>& pushConstants)
	{
		std::vector<VkPushConstantRange> pushCstRanges;
		pushCstRanges.reserve(pushConstants.size());

		for (auto& pushCst : pushConstants)
		{
			VkPushConstantRange& pCstRange = pushCstRanges.emplace_back();

			pCstRange.stageFlags = API_GetShaderStageFlags(pushCst.stageFlags);
			pCstRange.size = pushCst.size;
			pCstRange.offset = pushCst.offset;
		}

		return pushCstRanges;
	}

	void PipelineLayout::Create(const Device& _device,
		const std::vector<DescriptorSetLayout>& _descSetLayouts,
		const std::vector<PipelinePushConstantDescriptor>& pushConstants)
	{
		VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{};
		pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutCreateInfo.pNext = nullptr;
		pipelineLayoutCreateInfo.flags = 0u;

		// Descriptor Set Layouts
		{
			static_assert(sizeof(DescriptorSetLayout) == sizeof(VkDescriptorSetLayout), "Invalid reinterpret cast! Use ToVkDescriptorSetLayouts instead!");
			pipelineLayoutCreateInfo.pSetLayouts = reinterpret_cast<const VkDescriptorSetLayout*>(_descSetLayouts.data());

			//const std::vector<VkDescriptorSetLayout> vkDescSetLayout = ToVkDescriptorSetLayouts(_descSetLayouts);
			//pipelineLayoutCreateInfo.pSetLayouts = vkDescSetLayout.data();

			pipelineLayoutCreateInfo.setLayoutCount = SizeOf<uint32>(_descSetLayouts);
		}


		// Push Constants
		{
			const std::vector<VkPushConstantRange> pushCstRanges = FillPushConstantRanges(pushConstants);

			pipelineLayoutCreateInfo.pushConstantRangeCount = SizeOf<uint32>(pushCstRanges);
			pipelineLayoutCreateInfo.pPushConstantRanges = pushCstRanges.data();
		}


		SA_VK_ASSERT(vkCreatePipelineLayout(_device, &pipelineLayoutCreateInfo, nullptr, &mHandle), L"Failed to create pipeline layout!");

		SA_LOG("Pipeline Layout created.", Infos, SA/Render/Vulkan);
	}

	void PipelineLayout::Destroy(const Device& _device)
	{
		vkDestroyPipelineLayout(_device, mHandle, nullptr);
		mHandle = VK_NULL_HANDLE;

		SA_LOG("Pipeline Layout destroyed.", Infos, SA/Render/Vulkan);
	}


	PipelineLayout::operator VkPipelineLayout() const noexcept
	{
		return mHandle;
	}
}
