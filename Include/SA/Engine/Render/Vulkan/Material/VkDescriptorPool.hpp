// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_DESCRIPTOR_POOL_GUARD
#define SAPPHIRE_ENGINE_VK_DESCRIPTOR_POOL_GUARD

#include <vector>

#include <SA/Engine/Render/Vulkan/Material/VkDescriptorSet.hpp>
#include <SA/Engine/Render/Vulkan/Material/VkDescriptorSetLayout.hpp>

namespace SA
{
	struct PipelineBindingSetDescriptor;

	namespace VK
	{
		class Device;

		struct DescriptorPoolInfos
		{
			std::vector<VkDescriptorPoolSize> poolSizes;

			void AddBindings(const PipelineBindingSetDescriptor& _desc);
		};


		class DescriptorPool
		{
			VkDescriptorPool mHandle = VK_NULL_HANDLE;

		public:
			void Create(const Device& _device, const DescriptorPoolInfos& _infos);
			void Destroy(const Device& _device);

			DescriptorSet Allocate(const Device& _device, const DescriptorSetLayout& _layout);
			std::vector<DescriptorSet> Allocate(const Device& _device, const std::vector<DescriptorSetLayout>& _layouts);

			void Free(const Device& _device, DescriptorSet& _set);
			void Free(const Device& _device, std::vector<DescriptorSet>& _sets);

			operator VkDescriptorPool() const noexcept;
		};
	}
}

#endif // GUARD
