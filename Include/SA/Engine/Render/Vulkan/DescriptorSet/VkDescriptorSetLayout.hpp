// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHRE_ENGINE_VK_DESCRIPTOR_SET_LAYOUT_GUARD
#define SAPPHRE_ENGINE_VK_DESCRIPTOR_SET_LAYOUT_GUARD

#include <SA/Support/API/Vulkan.hpp>

namespace SA
{
	struct PipelineBindingSetDescriptor;

	namespace VK
	{
		class Device;

		class DescriptorSetLayout
		{
			VkDescriptorSetLayout mHandle = VK_NULL_HANDLE;

		public:
			void Create(const Device& _device, const PipelineBindingSetDescriptor& _desc);
			void Destroy(const Device& _device);

			operator VkDescriptorSetLayout() const noexcept;
		};

		static_assert(sizeof(DescriptorSetLayout) == sizeof(VkDescriptorSetLayout),
			"DescriptorSetLayout size must match VkDescriptorSetLayout. See utilization in VK::DescriptorPool.");
	}
}

#endif // GUARD
