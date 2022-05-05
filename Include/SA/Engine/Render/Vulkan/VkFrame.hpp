// Copyright(c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_FRAME_GUARD
#define SAPPHIRE_ENGINE_VK_FRAME_GUARD

#include <SA/Engine/Render/Base/ARenderFrame.hpp>

#include <SA/Engine/Render/Vulkan/Device/Command/VkCommandBuffer.hpp>
#include <SA/Engine/Render/Vulkan/Buffers/VkFrameBuffer.hpp>

namespace Sa::Vk
{
	struct Frame : public ARenderFrame
	{
		CommandBuffer cmd;
		FrameBuffer fBuff;
	};
}

#endif // GUARD
