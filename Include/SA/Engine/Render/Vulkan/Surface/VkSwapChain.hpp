// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_SWAP_CHAIN_GUARD
#define SAPPHIRE_ENGINE_VK_SWAP_CHAIN_GUARD

#include <vector>

#include <SA/Engine/Render/Vulkan/VkFrame.hpp>
// #include <SA/Engine/Render/Vulkan/Buffers/VkFrameBuffer.hpp>
// #include <SA/Engine/Render/Vulkan/Device/Command/VkCommandPool.hpp>

namespace Sa::Vk
{
	class Device;
	class Surface;

	class SwapChain
	{

//{ Swapchain KHR

		VkSwapchainKHR mHandle = VK_NULL_HANDLE;

		void CreateSwapChainKHR(const Device& _device, const Surface& _surface);
		void DestroySwapChainKHR(const Device& _device);
//}


//{ Sync

		struct Synchronisation
		{
			VkSemaphore acquireSemaphore = VK_NULL_HANDLE;
			VkSemaphore presentSemaphore = VK_NULL_HANDLE;
			VkFence		fence = VK_NULL_HANDLE;
		};

		void CreateSynchronisation(const Device& _device);
		void DestroySynchronisation(const Device& _device);
//}


//{ Command Buffer
		
		CommandPool mCmdPool;

		void CreateCommandBuffers(const Device& _device);
		void DestroyCommandBuffers(const Device& _device);

//}


//{ Frame

	uint32_t mImageNum = 1u;
	uint32_t mFrameIndex = 0u;
	uint32_t mImageIndex = 0u;

	struct SwapFrame : Frame
	{
		Synchronisation sync;
	};

	std::vector<SwapFrame> mFrames;

//}
		Vec2ui mExtent;
		Format mFormat = Format::sRGBA_32;

	public:
		Vec2ui GetExtent() const;
		Format GetFormat() const;

		void Create(const Device& _device, const Surface& _surface);
		void Destroy(const Device& _device);


		void CreateFrameBuffers(const Device& _device,
			const RenderPass& _renderPass,
			const RenderPassDescriptor& _renderPassDesc);
		void DestroyFrameBuffers(const Device& _device);


		Frame& Begin(const Device& _device);
		void End(const Device& _device);
	};
}

#endif // GUARD
