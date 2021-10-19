// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/VkFrame.hpp>

namespace Sa::Vk
{
	Frame::Frame(CommandBuffer& _cmd) noexcept :
		cmd{ _cmd }
	{
	}
}
