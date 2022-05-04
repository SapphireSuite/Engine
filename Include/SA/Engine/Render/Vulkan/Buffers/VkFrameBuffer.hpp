// Copyright(c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_FRAME_BUFFER_GUARD
#define SAPPHIRE_ENGINE_VK_FRAME_BUFFER_GUARD

#include <vector>

#include <SA/Engine/Render/Vulkan/Buffers/VkImageBuffer.hpp>

namespace Sa
{
	struct Color;
	struct RenderPassDescriptor;
}

namespace Sa::Vk
{
	class RenderPass;

	class FrameBuffer : public ABuffer
	{
		VkFramebuffer mHandle = VK_NULL_HANDLE;

		std::vector<ImageBuffer> mAttachments;
		std::vector<ImageBuffer> mInputAttachments;
		std::vector<VkClearValue> mClearValues;

		void AddClearColor(Format _format, const Color& _clearColor);

	public:
		const std::vector<VkClearValue>& GetClearValues() const;

		void Create(const Device& _device, const RenderPass& _renderPass,
			const RenderPassDescriptor& _rpDescriptor,
			const Vec2ui& _extent, VkImage presentImage = VK_NULL_HANDLE);
		void Destroy(const Device& _device);

		operator VkFramebuffer() const;
	};
}

#endif // GUARD
