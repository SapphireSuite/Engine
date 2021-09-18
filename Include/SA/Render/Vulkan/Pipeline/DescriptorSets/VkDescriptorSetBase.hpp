// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_DESCRIPTOR_SET_BASE_GUARD
#define SAPPHIRE_RENDER_VK_DESCRIPTOR_SET_BASE_GUARD

#include <SA/Core/Support/API/Vulkan.hpp>

#include <SA/Render/Base/Pipeline/DescriptorSets/DescriptorSetCreateInfos.hpp>


#if SA_VULKAN

namespace Sa::Vk
{
	class Device;

	class DescriptorSetBase
	{
		void CreateDescriptorPool(const Device& _device, const DescriptorSetCreateInfos& _infos);
		void DestroyDescriptorPool(const Device& _device);

	protected:
		VkDescriptorPool mDescriptorPool = VK_NULL_HANDLE;


		virtual void CreateDescriptorSets(const Device& _device, const DescriptorSetCreateInfos& _infos) = 0;
		virtual void UpdateDescriptorSets(const Device& _device, const std::vector<AShaderBinding*>& _bindings) = 0;
		virtual void DestroyDescriptorSets(const Device& _device) = 0;

	public:
		void Create(const Device& _device, const DescriptorSetCreateInfos& _infos);
		void Destroy(const Device& _device);
	};
}

#endif

#endif // GUARD
