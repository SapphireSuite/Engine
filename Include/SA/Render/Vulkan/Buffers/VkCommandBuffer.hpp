// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_COMMAND_BUFFER_GUARD
#define SAPPHIRE_RENDER_VK_COMMAND_BUFFER_GUARD

#include <SA/Core/Support/API/Vulkan.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class Device;

	class CommandBuffer
	{
		friend class CommandPool;

		VkCommandBuffer mHandle = VK_NULL_HANDLE;

	public:
		operator VkCommandBuffer() const;
	};
}

#endif

#endif // GUARD
