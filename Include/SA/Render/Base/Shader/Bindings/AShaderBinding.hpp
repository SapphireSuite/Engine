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
		/// Binding number in shader.
		const uint32 binding = 0u;

		/// Descriptor Index (if used with DescriptorMultiSet).
		const uint32 descriptor = ~uint32();


		AShaderBinding(uint32 _binding, uint32 _descriptor) noexcept;


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
