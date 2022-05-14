// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_CUBEMAP_GUARD
#define SAPPHIRE_ENGINE_VK_CUBEMAP_GUARD

#include <SA/Engine/Render/Base/Texture/ACubemap.hpp>
#include <SA/Engine/Render/Vulkan/Texture/VkTexture.hpp>

namespace SA::VK
{
	class Cubemap : public Texture, public ACubemap
	{
		ImageBuffer mIrradianceBuffer;

		using Texture::Create; // overloaded.
		using ACubemap::Create; // overloaded.
		using ACubemap::Destroy; // overloaded.

	public:
		void Create(const Device& _device, ResourceInitializer& _init, const RawCubemap& _raw);
		void Destroy(const Device& _device) override final;

		VkDescriptorImageInfo CreateIrradianceDescriptorImageInfo() const noexcept;
		static VkWriteDescriptorSet CreateWriteDescriptorSet(VkDescriptorSet _descriptorSet, uint32_t _binding, uint32_t _arrayElem = 0u) noexcept;
	};
}

#endif // GUARD
