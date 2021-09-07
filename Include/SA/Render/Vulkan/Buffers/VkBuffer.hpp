// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_BUFFER_GUARD
#define SAPPHIRE_RENDER_VK_BUFFER_GUARD

#include <SA/Core/Support/API/Vulkan.hpp>

#include <SA/Core/Types/Int.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class Device;

	class Buffer
	{
	public:
		static uint32 FindMemoryType(const Device& _device, uint32 _typeFilter, VkMemoryPropertyFlags _properties);
	};
}

#endif

#endif // GUARD
