// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_ABUFFER_GUARD
#define SAPPHIRE_ENGINE_VK_ABUFFER_GUARD

#include <cstdint>

#include <SA/Support/API/Vulkan.hpp>

namespace Sa::Vk
{
	class Device;

	class ABuffer
	{
	public:
		static uint32_t FindMemoryType(const Device& _device, uint32_t _typeFilter, VkMemoryPropertyFlags _properties);
	};
}

#endif // GUARD
