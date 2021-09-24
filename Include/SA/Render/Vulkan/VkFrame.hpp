// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_FRAME_GUARD
#define SAPPHIRE_RENDER_VK_FRAME_GUARD

#include <SA/Render/Base/ARenderFrame.hpp>

#include <SA/Render/Vulkan/Buffers/VkCommandBuffer.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class Frame : public ARenderFrame
	{
	public:
		CommandBuffer& cmd;

		Frame(CommandBuffer& _cmd) noexcept;
	};
}

#endif

#endif // GUARD
