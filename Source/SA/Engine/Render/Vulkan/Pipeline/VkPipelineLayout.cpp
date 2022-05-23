// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Pipeline/VkPipelineLayout.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>

namespace SA::VK
{
	std::vector<VkPushConstantRange> FillPushConstantRanges(const std::vector<PipelinePushConstantDescriptor>& _pushConstDescs)
	{
		std::vector<VkPushConstantRange> pushCstRanges;
		pushCstRanges.reserve(_pushConstDescs.size());

		for (auto& pushCstDesc : _pushConstDescs)
		{
			VkPushConstantRange& pCstRange = pushCstRanges.emplace_back();

			pCstRange.stageFlags = API_GetShaderStageFlags(pushCstDesc.stageFlags);
			pCstRange.size = pushCstDesc.size;
			pCstRange.offset = pushCstDesc.offset;
		}

		return pushCstRanges;
	}


	void PipelineLayout::CreateDescriptorSetLayouts(const Device& _device,
		const std::vector<PipelineBindingSetDescriptor>& _pipBindSetDescs)
	{
		mDescriptorSetLayouts.reserve(_pipBindSetDescs.size());

		// Re-use memory each loop.
		std::vector<VkDescriptorSetLayoutBinding> descSetLayout;

		for(auto it = _pipBindSetDescs.begin(); it != _pipBindSetDescs.end(); ++it)
		{
			descSetLayout.clear();
			descSetLayout.reserve(it->bindings.size());

			for (auto& bind : it->bindings)
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
			descriptorSetLayoutInfo.bindingCount = static_cast<uint32_t>(descSetLayout.size());
			descriptorSetLayoutInfo.pBindings = descSetLayout.data();

			VkDescriptorSetLayout& outLayout = mDescriptorSetLayouts.emplace_back();

			SA_VK_ASSERT(vkCreateDescriptorSetLayout(_device, &descriptorSetLayoutInfo, nullptr, &outLayout),
				L"Failed to create descriptor set layout!");
		}
	}

	void PipelineLayout::DestroyDescriptorSetLayouts(const Device& _device)
	{
		for(auto it = mDescriptorSetLayouts.begin(); it != mDescriptorSetLayouts.end(); ++it)
			vkDestroyDescriptorSetLayout(_device, *it, nullptr);

		mDescriptorSetLayouts.clear();
	}


	void PipelineLayout::CreatePipelineLayout(const Device& _device,
		const std::vector<PipelinePushConstantDescriptor>& _pushConstDescs)
	{
		VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{};
		pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutCreateInfo.pNext = nullptr;
		pipelineLayoutCreateInfo.flags = 0u;


		// Descriptor Set Layouts
		pipelineLayoutCreateInfo.pSetLayouts = mDescriptorSetLayouts.data();
		pipelineLayoutCreateInfo.setLayoutCount = static_cast<uint32_t>(mDescriptorSetLayouts.size());


		// Push Constants
		const std::vector<VkPushConstantRange> pushCstRanges = FillPushConstantRanges(_pushConstDescs);
		pipelineLayoutCreateInfo.pushConstantRangeCount = static_cast<uint32_t>(pushCstRanges.size());
		pipelineLayoutCreateInfo.pPushConstantRanges = pushCstRanges.data();
		

		SA_VK_ASSERT(vkCreatePipelineLayout(_device, &pipelineLayoutCreateInfo, nullptr, &mHandle),
			L"Failed to create pipeline layout!");
	}
	
	void PipelineLayout::DestroyPipelineLayout(const Device& _device)
	{
		vkDestroyPipelineLayout(_device, mHandle, nullptr);
		mHandle = VK_NULL_HANDLE;
	}


	void PipelineLayout::Create(const Device& _device, const RenderPipelineLayoutDescriptor& _desc)
	{
		ARenderPipelineLayout::Create();

		CreateDescriptorSetLayouts(_device, _desc.bindSetDescs);

		CreatePipelineLayout(_device, _desc.pushConstDescs);

		SA_LOG(L"Pipeline Layout created.", Infos, SA/Engine/Render/Vulkan);
	}

	void PipelineLayout::Destroy(const Device& _device)
	{
		ARenderPipelineLayout::Destroy();

		DestroyDescriptorSetLayouts(_device);

		DestroyPipelineLayout(_device);

		SA_LOG(L"Pipeline Layout destroyed.", Infos, SA/Engine/Render/Vulkan);
	}

	PipelineLayout::operator VkPipelineLayout() const noexcept
	{
		return mHandle;
	}
}
