// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_VK_FRAME_BUFFER_GUARD
#define SAPPHIRE_RENDER_VK_FRAME_BUFFER_GUARD

#include <SA/Render/Base/AFrameBuffer.hpp>

#include <SA/Render/Base/Pass/RenderPassDescriptor.hpp>

#include <SA/Render/Vulkan/Buffers/VkImageBuffer.hpp>


#if SA_VULKAN

namespace Sa::Vk
{
	class Device;
	class RenderPass;

	class FrameBuffer : public AFrameBuffer
	{
		VkFramebuffer mHandle = VK_NULL_HANDLE;

		std::vector<ImageBuffer> mAttachments;
		std::vector<ImageBuffer> mInputAttachments;
		std::vector<VkClearValue> mClearValues;

		void AddClearColor(Format _format, const Color& _clearColor);

	public:
		void Create(const Device& _device, const RenderPass& _renderPass,
			const RenderPassDescriptor& _rpDescriptor,
			const Vec2ui& _extent, uint32 _poolIndex = 0u, VkImage presentImage = VK_NULL_HANDLE);
		void Destroy(const Device& _device);

		void Begin() override final;
		void NextSubpass() override final;
		void End() override final;
	};
}

#endif

#endif // GUARD
