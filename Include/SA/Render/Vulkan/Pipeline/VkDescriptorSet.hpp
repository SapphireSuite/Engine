// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_DESCRIPTOR_SET_GUARD
#define SAPPHIRE_RENDER_VK_DESCRIPTOR_SET_GUARD

#include <vector>

#include <SA/Core/Support/API/Vulkan.hpp>

#if SA_VULKAN

namespace Sa
{
	struct PipelineBindingSetDescriptor;
	class ARenderMaterialBinding;
}

namespace Sa::Vk
{
	class Device;
	class Pipeline;

	class DescriptorSet
	{
		VkDescriptorSet mHandle = VK_NULL_HANDLE;
		VkDescriptorPool mDescriptorPool = VK_NULL_HANDLE;


		void CreateDescriptorPool(const Device& _device, const PipelineBindingSetDescriptor& _infos);
		void DestroyDescriptorPool(const Device& _device);


		void CreateDescriptorSet(const Device& _device, VkDescriptorSetLayout _descSetLayout);
		void DestroyDescriptorSet(const Device& _device);

	public:
		void Create(const Device& _device, const PipelineBindingSetDescriptor& _infos, VkDescriptorSetLayout _descSetLayout);
		void Destroy(const Device& _device);

		void Update(const Device& _device, const std::vector<const ARenderMaterialBinding*>& _bindings);
	};
}

#endif

#endif // GUARD
