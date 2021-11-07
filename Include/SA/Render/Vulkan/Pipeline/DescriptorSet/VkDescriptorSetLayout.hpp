// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_DESCRIPTOR_SET_LAYOUT_GUARD
#define SAPPHIRE_RENDER_VK_DESCRIPTOR_SET_LAYOUT_GUARD

#include <SA/Core/Support/API/Vulkan.hpp>

#include <SA/Render/Base/Pipeline/Descriptors/PipelineBindingSetDescriptor.hpp>

namespace Sa::Vk
{
	class Device;

	class DescriptorSetLayout
	{
		VkDescriptorSetLayout mHandle;

	public:
		const VkDescriptorSetLayout& GetHandle() const noexcept;

		void Create(const Device& _device, const PipelineBindingSetDescriptor& _pipBindSetDesc);
		void Destroy(const Device& _device);

		operator VkDescriptorSetLayout() const noexcept;
	};
}

#endif // GUARD
