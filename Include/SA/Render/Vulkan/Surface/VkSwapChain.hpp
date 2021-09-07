// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_SWAP_CHAIN_GUARD
#define SAPPHIRE_RENDER_VK_SWAP_CHAIN_GUARD

#include <vector>

#include <SA/Core/Support/API/Vulkan.hpp>

#include <SA/Core/Types/Int.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class Device;
	class RenderSurface;

	class SwapChain
	{
		VkSwapchainKHR mHandle = VK_NULL_HANDLE;

		//Vec2ui mExtent;

		uint32 mImageNum = 1u;
		//uint32 mFrameIndex = 0u;
		//uint32 mImageIndex = 0u;

		struct Synchronisation
		{
			VkSemaphore acquireSemaphore = VK_NULL_HANDLE;
			VkSemaphore presentSemaphore = VK_NULL_HANDLE;
			VkFence		fence = VK_NULL_HANDLE;
		};

		std::vector<Synchronisation> mFramesSynch;


		void CreateSwapChainKHR(const Device& _device, const RenderSurface& _surface);
		void DestroySwapChainKHR(const Device& _device);

		void CreateSynchronisation(const Device& _device);
		void DestroySynchronisation(const Device& _device);

	public:
		void Create(const Device& _device, const RenderSurface& _surface);
		void Destroy(const Device& _device);
	};
}

#endif

#endif // GUARD
