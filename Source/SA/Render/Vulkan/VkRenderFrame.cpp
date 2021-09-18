// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/VkRenderFrame.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	RenderFrame::RenderFrame(CommandBuffer& _cmd) noexcept :
		cmd{ _cmd }
	{
	}
}

#endif
