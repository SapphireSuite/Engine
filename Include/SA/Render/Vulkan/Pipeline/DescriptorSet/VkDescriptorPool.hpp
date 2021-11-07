// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_DESCIPTOR_POOL_GUARD
#define SAPPHIRE_RENDER_VK_DESCIPTOR_POOL_GUARD

#include <vector>

#include <SA/Render/Base/Pipeline/Descriptors/PipelineBindingSetDescriptor.hpp>

#include <SA/Render/Vulkan/Pipeline/DescriptorSet/VkDescriptorSet.hpp>

namespace Sa::Vk
{
	class Device;
	class DescriptorSetLayout;

	class  DescriptorPool
	{
		VkDescriptorPool mHandle = VK_NULL_HANDLE;

	public:
		void Create(const Device& _device, const PipelineBindingSetDescriptor& _bindSetDesc, uint32 _maxSet = 0);
		void Destroy(const Device& _device);

		DescriptorSet Allocate(const Device& _device, const DescriptorSetLayout& _layout);
		std::vector<DescriptorSet> Allocate(const Device& _device, const std::vector<DescriptorSetLayout>& _layouts);

		void Free(const Device& _device, DescriptorSet& _descSet);
		void Free(const Device& _device, std::vector<DescriptorSet>& _descSets);

		operator VkDescriptorPool() const noexcept;
	};
}

#endif // GUARD
