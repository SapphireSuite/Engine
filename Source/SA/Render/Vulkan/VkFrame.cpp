// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/VkFrame.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	Frame::Frame(CommandBuffer& _cmd) noexcept :
		cmd{ _cmd }
	{
	}
}

#endif
