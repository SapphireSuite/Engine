// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_TEXTURE_GUARD
#define SAPPHIRE_ENGINE_VK_TEXTURE_GUARD

#include <SA/Engine/Render/Base/Texture/ATexture.hpp>

#include <SA/Engine/Render/Vulkan/Buffers/VkImageBuffer.hpp>
#include <SA/Engine/Render/Vulkan/Texture/VkTextureSampler.hpp>

namespace SA::VK
{
	class Texture : public ATexture
	{
	protected:
		ImageBuffer mBuffer;

		// TODO: Sampler is not link to 1 image: Use 1 for multiple image!
		TextureSampler mSampler;

		using ATexture::Create; // overloaded.
		using ATexture::Destroy; // overloaded.

	public:
		void Create(const Device& _device, ResourceInitializer& _init, const RawTexture& _raw);
		virtual void Destroy(const Device& _device);

		VkDescriptorImageInfo CreateDescriptorImageInfo() const noexcept;
	};
}

#endif // GUARD
