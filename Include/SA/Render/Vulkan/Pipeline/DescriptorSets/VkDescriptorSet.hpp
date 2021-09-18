// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_DESCRIPTOR_SET_GUARD
#define SAPPHIRE_RENDER_VK_DESCRIPTOR_SET_GUARD

#include <SA/Render/Vulkan/Pipeline/DescriptorSets/VkDescriptorSetBase.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class DescriptorSet : public DescriptorSetBase
	{
		VkDescriptorSet mDescriptorSet = VK_NULL_HANDLE;

		void CreateDescriptorSets(const Device& _device, const DescriptorSetCreateInfos& _infos) override final;
		void UpdateDescriptorSets(const Device& _device, const std::vector<AShaderBinding*>& _bindings) override final;
		void DestroyDescriptorSets(const Device& _device) override final;
	};
}

#endif

#endif // GUARD
