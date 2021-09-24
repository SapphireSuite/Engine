// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_RENDER_PASS_GUARD
#define SAPPHIRE_RENDER_VK_RENDER_PASS_GUARD

#include <SA/Render/Base/Pass/ARenderPass.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class CommandBuffer;
	class FrameBuffer;

	class RenderPass : public ARenderPass
	{
		VkRenderPass mHandle = VK_NULL_HANDLE;

	public:
		void Create(const ARenderDevice* _device, const RenderPassDescriptor& _descriptor) override final;
		void Destroy(const ARenderDevice* _device) override final;

		void Begin(CommandBuffer& _cmdBuff, const FrameBuffer& _frameBuff);
		void NextSubpass(CommandBuffer& _cmdBuff);
		void End(CommandBuffer& _cmdBuff);

		operator VkRenderPass() const noexcept;
	};
}

#endif

#endif // GUARD
