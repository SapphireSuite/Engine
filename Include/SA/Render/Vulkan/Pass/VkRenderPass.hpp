// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_RENDER_PASS_GUARD
#define SAPPHIRE_RENDER_VK_RENDER_PASS_GUARD

#include <SA/Core/Support/API/Vulkan.hpp>

namespace Sa
{
	struct RenderPassDescriptor;
};

namespace Sa::Vk
{
	class Device;
	//class CommandBuffer;
	//class FrameBuffer;

	class RenderPass
	{
		VkRenderPass mHandle = VK_NULL_HANDLE;

	public:
		void Create(const Device& _device, const RenderPassDescriptor& _descriptor);
		void Destroy(const Device& _device);

		//void Begin(CommandBuffer& _cmdBuff, const FrameBuffer& _frameBuff);
		//void NextSubpass(CommandBuffer& _cmdBuff);
		//void End(CommandBuffer& _cmdBuff);

		operator VkRenderPass() const noexcept;
	};
}

#endif // GUARD
