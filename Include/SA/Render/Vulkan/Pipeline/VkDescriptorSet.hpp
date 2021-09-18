// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_DESCRIPTOR_SET_GUARD
#define SAPPHIRE_RENDER_VK_DESCRIPTOR_SET_GUARD

#include <SA/Render/Base/Pipeline/DescriptorSets/ADescriptorSet.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class Device;

	class DescriptorSet : public ADescriptorSet
	{
		VkDescriptorPool mDescriptorPool = VK_NULL_HANDLE;
		std::vector<VkDescriptorSet> mDescriptorSets;


		void CreateDescriptorPool(const Device& _device, const DescriptorSetCreateInfos& _infos, uint32 _descSetNum);
		void DestroyDescriptorPool(const Device& _device);


		void CreateDescriptorSets(const Device& _device, const DescriptorSetCreateInfos& _infos, uint32 _descSetNum);
		void UpdateDescriptorSets(const Device& _device, const std::vector<AShaderBinding*>& _bindings);
		void DestroyDescriptorSets(const Device& _device);

	public:
		void Create(const Device& _device, const DescriptorSetCreateInfos& _infos);
		void Destroy(const Device& _device);

		void Bind(const ARenderFrame& _frame, const APipeline& _pipeline) const override final;
	};
}

#endif

#endif // GUARD
