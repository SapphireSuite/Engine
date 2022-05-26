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

			pCstRange.stageFlags = API_GetShaderStageFlags(pushCstDesc.stage);
			pCstRange.size = pushCstDesc.size;
			pCstRange.offset = pushCstDesc.offset;
		}

		return pushCstRanges;
	}

	const std::vector<DescriptorSetLayout>& PipelineLayout::GetDescriptorSetLayouts() const noexcept
	{
		return mDescriptorSetLayouts;
	}


	void PipelineLayout::CreateDescriptorSetLayouts(const Device& _device,
		const std::vector<PipelineBindingSetDescriptor>& _pipBindSetDescs)
	{
		mDescriptorSetLayouts.reserve(_pipBindSetDescs.size());

		for(auto it = _pipBindSetDescs.begin(); it != _pipBindSetDescs.end(); ++it)
		{
			DescriptorSetLayout& descSetLayout = mDescriptorSetLayouts.emplace_back();
			
			descSetLayout.Create(_device, *it);
		}
	}

	void PipelineLayout::DestroyDescriptorSetLayouts(const Device& _device)
	{
		for(auto it = mDescriptorSetLayouts.begin(); it != mDescriptorSetLayouts.end(); ++it)
			it->Destroy(_device);

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
		pipelineLayoutCreateInfo.pSetLayouts = reinterpret_cast<const VkDescriptorSetLayout*>(mDescriptorSetLayouts.data());
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

		SA_LOG(L"Pipeline Layout [" << mHandle << L"] created.", Infos, SA/Engine/Render/Vulkan);
	}

	void PipelineLayout::Destroy(const Device& _device)
	{
		ARenderPipelineLayout::Destroy();

		DestroyDescriptorSetLayouts(_device);

		SA_LOG(L"Pipeline Layout [" << mHandle << L"] destroyed.", Infos, SA/Engine/Render/Vulkan);

		DestroyPipelineLayout(_device);
	}

	PipelineLayout::operator VkPipelineLayout() const noexcept
	{
		return mHandle;
	}
}
