// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_ARENDER_MATERIAL_BINDING_GUARD
#define SAPPHIRE_ENGINE_ARENDER_MATERIAL_BINDING_GUARD

#include <cstdint>

#if SA_VULKAN

	#include <SA/Engine/Render/Vulkan/Material/VkDescriptorSetUpdater.hpp>

#endif

namespace SA
{
	class ARenderMaterialBinding
	{
	public:
		uint32_t binding = 0u;
		uint32_t set = 0u;

		ARenderMaterialBinding() = default;
		ARenderMaterialBinding(uint32_t _binding, uint32_t _set) noexcept;
		virtual ~ARenderMaterialBinding() = default;

	#if SA_VULKAN

		virtual VkDescriptorType GetVkDescriptorType() const noexcept = 0;
	
		virtual VkWriteDescriptorSet MakeVkDescriptors(VK::DescriptorSetUpdater& _updater) const = 0;

	#endif
	};
}

#endif // GUARD
