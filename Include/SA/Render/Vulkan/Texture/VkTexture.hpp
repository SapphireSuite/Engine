// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_TEXTURE_GUARD
#define SAPPHIRE_RENDER_VK_TEXTURE_GUARD

#include <SA/Core/Support/API/Vulkan.hpp>

#include <SA/Render/Base/Texture/ATexture.hpp>

#include <SA/Render/Vulkan/Buffers/VkImageBuffer.hpp>
#include <SA/Render/Vulkan/Texture/VkTextureSampler.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class Texture : public ATexture
	{
		ImageBuffer mBuffer;

		// TODO: Sampler is not link to 1 image: Use 1 for multiple image!
		TextureSampler mSampler;

	public:
		void Create(ARenderResourceInitializer* _init, const RawTexture& _raw) override final;
		void Destroy(const ARenderDevice* _device) override final;

		VkDescriptorImageInfo CreateDescriptorImageInfo() const noexcept;
	};
}

#endif

#endif // GUARD
