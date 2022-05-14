// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_TEXTURE_SAMPLER_GUARD
#define SAPPHIRE_ENGINE_VK_TEXTURE_SAMPLER_GUARD

#include <cstdint>

#include <SA/Support/API/Vulkan.hpp>

namespace SA::VK
{
	class Device;

	class TextureSampler
	{
		VkSampler mHandle = VK_NULL_HANDLE;

	public:
		void Create(const Device& _device, uint32_t _mipLevels);
		void Destroy(const Device& _device);

		operator VkSampler() const;
	};
}

#endif // GUARD
