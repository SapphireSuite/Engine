// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_TEXTURE_SAMPLER_GUARD
#define SAPPHIRE_RENDER_VK_TEXTURE_SAMPLER_GUARD

#include <SA/Core/Types/Int.hpp>

#include <SA/Core/Support/API/Vulkan.hpp>

namespace Sa::Vk
{
	class Device;

	class TextureSampler
	{
		VkSampler mHandle = VK_NULL_HANDLE;

	public:
		void Create(const Device& _device, uint32 _mipLevels);
		void Destroy(const Device& _device);

		operator VkSampler() const;
	};
}

#endif // GUARD
