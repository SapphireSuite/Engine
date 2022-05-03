// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_SWAP_CHAIN_GUARD
#define SAPPHIRE_ENGINE_VK_SWAP_CHAIN_GUARD

#include <vector>

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Engine/Render/Base/Misc/Format.hpp>

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

		std::vector<Synchronisation> mFramesSynch;


		void CreateSynchronisation(const Device& _device);
		void DestroySynchronisation(const Device& _device);
//}

		Vec2ui mExtent;
		Format mFormat = Format::sRGBA_32;

		uint32_t mImageNum = 1u;
		uint32_t mFrameIndex = 0u;
		uint32_t mImageIndex = 0u;

	public:
		Format GetFormat() const;

		void Create(const Device& _device, const Surface& _surface);
		void Destroy(const Device& _device);
	};
}

#endif // GUARD
