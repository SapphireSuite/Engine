// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Buffers/VkCommandBuffer.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	CommandBuffer::operator VkCommandBuffer() const
	{
		return mHandle;
	}
}

#endif
