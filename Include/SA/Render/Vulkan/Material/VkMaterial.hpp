// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_MATERIAL_GUARD
#define SAPPHIRE_RENDER_VK_MATERIAL_GUARD

#include <SA/Render/Base/Material/AMaterial.hpp>

#include <SA/Core/Support/API/Vulkan.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class Device;
	class CommandBuffer;

	class Material : public AMaterial
	{
		VkDescriptorPool mDescriptorPool = VK_NULL_HANDLE;
		std::vector<VkDescriptorSet> mDescriptorSets;

		void CreateDescriptorPool(const Device& _device, const MaterialCreateInfos& _infos);
		void DestroyDescriptorPool(const Device& _device);


		void CreateDescriptorSets(const Device& _device, const MaterialCreateInfos& _infos);
		void UpdateDescriptorSets(const Device& _device, const std::vector<AMaterialBinding*>& _bindings);
		void DestroyDescriptorSets(const Device& _device);

	public:
		void Create(const Device& _device, const MaterialCreateInfos& _infos);
		void Destroy(const Device& _device);

		void Bind(CommandBuffer& _cmd, const APipeline& _pipeline);
	};
}

#endif

#endif // GUARD
