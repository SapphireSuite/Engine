// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_PIPELINE_LAYOUT_GUARD
#define SAPPHIRE_RENDER_VK_PIPELINE_LAYOUT_GUARD

#include <vector>

#include <SA/Core/Support/API/Vulkan.hpp>

#include <Render/Base/Pipeline/Descriptors/PipelinePushConstantDescriptor.hpp>

namespace Sa::Vk
{
	class Device;
	class DescriptorSetLayout;

	class PipelineLayout
	{
		VkPipelineLayout mHandle = VK_NULL_HANDLE;

	public:
		void Create(const Device& _device,
			const std::vector<DescriptorSetLayout>& _descSetLayouts,
			const std::vector<PipelinePushConstantDescriptor>& pushConstants);
		void Destroy(const Device& _device);

		operator VkPipelineLayout() const noexcept;
	};
}

#endif // GUARD
