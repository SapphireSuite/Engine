// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_TEXTURE_GUARD
#define SAPPHIRE_RENDER_VK_TEXTURE_GUARD

#include <SA/Render/Base/Texture/ATexture.hpp>

#include <SA/Render/Vulkan/Buffers/VkImageBuffer.hpp>
#include <SA/Render/Vulkan/Texture/VkTextureSampler.hpp>

namespace Sa::Vk
{
	class Texture : public ATexture
	{
	protected:
		ImageBuffer mBuffer;

		// TODO: Sampler is not link to 1 image: Use 1 for multiple image!
		TextureSampler mSampler;

	public:
		void Create(const Device& _device, ResourceInitializer& _init, const RawTexture& _raw);
		virtual void Destroy(const Device& _device);

		VkDescriptorImageInfo CreateDescriptorImageInfo() const noexcept;
	};
}

#endif // GUARD
