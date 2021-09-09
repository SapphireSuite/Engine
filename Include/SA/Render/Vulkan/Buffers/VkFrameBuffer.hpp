// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_VK_FRAME_BUFFER_GUARD
#define SAPPHIRE_RENDER_VK_FRAME_BUFFER_GUARD

#include <SA/Render/Base/Pass/RenderPassDescriptor.hpp>

#include <SA/Render/Vulkan/Buffers/VkImageBuffer.hpp>


#if SA_VULKAN

namespace Sa::Vk
{
	class Device;
	class RenderPass;
	class CommandBuffer;

	class FrameBuffer
	{
		VkFramebuffer mHandle = VK_NULL_HANDLE;
		VkRenderPass mRenderPass = VK_NULL_HANDLE;

		Vec2ui mExtent;

		std::vector<ImageBuffer> mAttachments;
		std::vector<ImageBuffer> mInputAttachments;
		std::vector<VkClearValue> mClearValues;

		void AddClearColor(Format _format, const Color& _clearColor);

	public:
		void Create(const Device& _device, const RenderPass& _renderPass,
			const RenderPassDescriptor& _rpDescriptor,
			const Vec2ui& _extent, VkImage presentImage = VK_NULL_HANDLE);
		void Destroy(const Device& _device);

		void Begin(CommandBuffer& _cmdBuff);
		void NextSubpass(CommandBuffer& _cmdBuff);
		void End(CommandBuffer& _cmdBuff);
	};
}

#endif

#endif // GUARD
