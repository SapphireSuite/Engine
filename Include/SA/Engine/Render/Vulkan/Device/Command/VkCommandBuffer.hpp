// Copyright (c) 20212 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_COMMAND_BUFFER_GUARD
#define SAPPHIRE_ENGINE_VK_COMMAND_BUFFER_GUARD

#include <SA/Support/API/Vulkan.hpp>

namespace Sa::Vk
{
	class CommandBuffer
	{
		friend class CommandPool;

		VkCommandBuffer mHandle = VK_NULL_HANDLE;

	public:
		void Begin();
		void End();

		operator VkCommandBuffer() const;
	};
}

#endif // GUARD
