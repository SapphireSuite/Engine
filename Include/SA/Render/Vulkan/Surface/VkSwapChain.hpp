// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_SWAP_CHAIN_GUARD
#define SAPPHIRE_RENDER_VK_SWAP_CHAIN_GUARD

#include <vector>

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Render/Base/Misc/Format.hpp>

#include <SA/Render/Vulkan/Buffers/VkFrameBuffer.hpp>

namespace Sa::Vk
{
	class Device;
	class Surface;

	class SwapChain
	{
		VkSwapchainKHR mHandle = VK_NULL_HANDLE;

		Vec2ui mExtent;
		Format mFormat = Format::sRGBA_32;

		uint32 mImageNum = 1u;
		uint32 mFrameIndex = 0u;
		uint32 mImageIndex = 0u;

		struct Synchronisation
		{
			VkSemaphore acquireSemaphore = VK_NULL_HANDLE;
			VkSemaphore presentSemaphore = VK_NULL_HANDLE;
			VkFence		fence = VK_NULL_HANDLE;
		};

		std::vector<Synchronisation> mFramesSynch;
		std::vector<FrameBuffer> mFrameBuffers;

		void CreateSwapChainKHR(const Device& _device, const Surface& _surface);
		void DestroySwapChainKHR(const Device& _device);

		void CreateSynchronisation(const Device& _device);
		void DestroySynchronisation(const Device& _device);

	public:
		Format GetFormat() const;

		void Create(const Device& _device, const Surface& _surface);
		void Destroy(const Device& _device);

		void CreateFrameBuffers(const Device& _device, const RenderPass& _renderPass, const RenderPassDescriptor& _renderPassDesc);
		void DestroyFrameBuffers(const Device& _device);

		FrameBuffer& Begin(const Device& _device);
		void End(const Device& _device, const std::vector<CommandBuffer>& _cmdBuffers);
	};
}

#endif // GUARD
