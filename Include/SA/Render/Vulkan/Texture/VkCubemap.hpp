// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_CUBEMAP_GUARD
#define SAPPHIRE_RENDER_VK_CUBEMAP_GUARD

#include <SA/Render/Base/Texture/ACubemap.hpp>
#include <SA/Render/Vulkan/Texture/VkTexture.hpp>

namespace Sa::Vk
{
	class Cubemap : public Texture, public ACubemap
	{
		ImageBuffer mIrradianceBuffer;

		using Texture::Create;

	public:
		void Create(const Device& _device, ResourceInitializer& _init, const RawCubemap& _raw);
		void Destroy(const Device& _device) override final;

		VkDescriptorImageInfo CreateIrradianceDescriptorImageInfo() const noexcept;
		static VkWriteDescriptorSet CreateWriteDescriptorSet(VkDescriptorSet _descriptorSet, uint32 _binding, uint32 _arrayElem = 0u) noexcept;
	};
}

#endif // GUARD
