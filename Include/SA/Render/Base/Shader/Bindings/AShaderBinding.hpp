// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ASHADER_BINDING_GUARD
#define SAPPHIRE_RENDER_ASHADER_BINDING_GUARD

#include <SA/Core/Types/Abstract.hpp>

#include <SA/Core/Support/API/Vulkan.hpp>

namespace Sa
{
	class AShaderBinding : public Abstract
	{
	public:
		/// Binding index in shader.
		uint32 binding = 0u;

		/// Descriptor set index in shader.
		uint32 set = 0;


		AShaderBinding(uint32 _binding, uint32 _set = 0u) noexcept;


		virtual ~AShaderBinding() = default;


#if SA_VULKAN

		virtual VkDescriptorType GetVkDescriptorType() const noexcept = 0;

		virtual VkWriteDescriptorSet MakeVkDescriptors(
			std::list<std::vector<VkDescriptorBufferInfo>>& _bufferDescs,
			std::list<std::vector<VkDescriptorImageInfo>>& _imageDescs) const = 0;

#endif
	};
}

#endif // GUARD
