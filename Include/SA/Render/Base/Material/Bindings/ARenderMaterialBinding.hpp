// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ARENDER_MATERIAL_BINDING_GUARD
#define SAPPHIRE_RENDER_ARENDER_MATERIAL_BINDING_GUARD

#include <list>
#include <vector>

#include <SA/Core/Types/Int.hpp>

#include <SA/Core/Support/API/Vulkan.hpp>

namespace Sa
{
	class ARenderMaterialBinding
	{
	public:
		/// Binding index in shader.
		uint32 binding = 0u;


		ARenderMaterialBinding(uint32 _binding) noexcept;


#if SA_VULKAN

		virtual VkDescriptorType GetVkDescriptorType() const noexcept = 0;

		virtual VkWriteDescriptorSet MakeVkDescriptors(
			std::list<std::vector<VkDescriptorBufferInfo>>& _bufferDescs,
			std::list<std::vector<VkDescriptorImageInfo>>& _imageDescs) const = 0;

#endif
	};
}

#endif // GUARD
