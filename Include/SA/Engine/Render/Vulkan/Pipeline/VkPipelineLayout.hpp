// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHRIRE_ENGINE_VK_PIPELINE_LAYOUT_GUARD
#define SAPPHRIRE_ENGINE_VK_PIPELINE_LAYOUT_GUARD

#include <SA/Support/API/Vulkan.hpp>

#include <SA/Engine/Render/Base/Pipeline/ARenderPipelineLayout.hpp>

namespace SA
{
	struct PipelineBindingSetDescriptor;
	struct PipelinePushConstantDescriptor;
}

namespace SA::VK
{
	class Device;

	class PipelineLayout : public ARenderPipelineLayout
	{
		VkPipelineLayout mHandle = VK_NULL_HANDLE;

		std::vector<VkDescriptorSetLayout> mDescriptorSetLayouts;

		using ARenderPipelineLayout::Create; // overload.
		using ARenderPipelineLayout::Destroy; // overload.
	
		void CreateDescriptorSetLayouts(const Device& _device,
			const std::vector<PipelineBindingSetDescriptor>& _pipBindSetDescs);
		void DestroyDescriptorSetLayouts(const Device& _device);

		void CreatePipelineLayout(const Device& _device,
			const std::vector<PipelinePushConstantDescriptor>& _pushConstDescs);
		void DestroyPipelineLayout(const Device& _device);

	public:
		void Create(const Device& _device, const RenderPipelineLayoutDescriptor& _desc);
		void Destroy(const Device& _device);
	};
}

#endif // GUARD
