// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_CUBEMAP_GUARD
#define SAPPHIRE_RENDER_VK_CUBEMAP_GUARD

#include <SA/Render/Base/Texture/ACubemap.hpp>

#include <SA/Render/Vulkan/Buffers/VkImageBuffer.hpp>
#include <SA/Render/Vulkan/Texture/VkTextureSampler.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class Cubemap : public ACubemap
	{
		ImageBuffer mBuffer;
		ImageBuffer mIrradianceBuffer;

		// TODO: Sampler is not link to 1 image: Use 1 for multiple image!
		TextureSampler mSampler;

	public:
		void Create(const Device& _device, ResourceInitializer& _init, const RawCubemap& _raw);
		void Destroy(const Device& _device);

		VkDescriptorImageInfo CreateDescriptorImageInfo() const noexcept;
		VkDescriptorImageInfo CreateIrradianceDescriptorImageInfo() const noexcept;
		static VkWriteDescriptorSet CreateWriteDescriptorSet(VkDescriptorSet _descriptorSet, uint32 _binding, uint32 _arrayElem = 0u) noexcept;
	};
}

#endif

#endif // GUARD
