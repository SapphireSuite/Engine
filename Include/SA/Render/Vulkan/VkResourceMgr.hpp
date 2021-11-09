// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_RESOURCE_MGR_GUARD
#define SAPPHIRE_RENDER_VK_RESOURCE_MGR_GUARD

#include <vector>

#include <SA/Render/Vulkan/Pipeline/DescriptorSet/VkDescriptorPool.hpp>
#include <SA/Render/Vulkan/Pipeline/DescriptorSet/VkDescriptorSetLayout.hpp>

namespace Sa::Vk
{
	class CGPUBuffer;

	class ResourceMgr
	{
		DescriptorPool mDescriptorPool;
		DescriptorSetLayout mDescriptorSetLayout;

		std::vector<DescriptorSet> mDescriptorSets;

	protected:
		virtual void FillDescriptorUpdater(DescriptorSet::Updater& _updater, uint32 _frame) = 0;
		void UpdateBuffer(const Device& _device, CGPUBuffer& _buffer, uint32 _binding, const void* _data, uint64 _octSize, uint32 _frame);

		void Create(const Device& _device, const PipelineBindingSetDescriptor& _bindSetDesc, uint32 _frameNum);

	public:
		const DescriptorSet& GetDescriptorSet(uint32 _frame) const;

		virtual void Destroy(const Device& _device);
	};
}

#endif // GUARD
