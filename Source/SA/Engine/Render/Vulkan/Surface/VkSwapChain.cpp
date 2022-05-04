// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Surface/VkSwapChain.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>

#include <Render/Vulkan/Device/VkDevice.hpp>

#include <Render/Vulkan/Surface/VkSurface.hpp>
#include <Render/Vulkan/Surface/VkSurfaceSupportDetails.hpp>

namespace Sa::Vk
{
	Format SwapChain::GetFormat() const
	{
		return mFormat;
	}


	void SwapChain::CreateSwapChainKHR(const Device& _device, const Surface& _surface)
	{
		SurfaceSupportDetails details = _surface.QuerySupportDetails(_device);

		VkSurfaceFormatKHR surfaceFormat = details.ChooseSwapSurfaceFormat();
		VkPresentModeKHR presentMode = details.ChooseSwapPresentMode();
		mExtent = details.ChooseSwapExtent();

		mFormat = API_FromFormat(surfaceFormat.format);

		// Min image count to avoid driver blocking.
		mImageNum = details.capabilities.minImageCount + 1;

		if (details.capabilities.maxImageCount > 0 && mImageNum > details.capabilities.maxImageCount)
			mImageNum = details.capabilities.maxImageCount;


		// Create Swapchain.
		VkSwapchainCreateInfoKHR swapChainCreateInfo{};
		swapChainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		swapChainCreateInfo.pNext = nullptr;
		swapChainCreateInfo.flags = 0u;
		swapChainCreateInfo.surface = _surface;
		swapChainCreateInfo.minImageCount = mImageNum;
		swapChainCreateInfo.imageFormat = surfaceFormat.format;
		swapChainCreateInfo.imageColorSpace = surfaceFormat.colorSpace;
		swapChainCreateInfo.imageExtent = VkExtent2D{ mExtent.x, mExtent.y };
		swapChainCreateInfo.imageArrayLayers = 1u;
		swapChainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		swapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		swapChainCreateInfo.queueFamilyIndexCount = 0u;
		swapChainCreateInfo.pQueueFamilyIndices = nullptr;
		swapChainCreateInfo.preTransform = details.capabilities.currentTransform;
		swapChainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		swapChainCreateInfo.presentMode = presentMode;
		swapChainCreateInfo.clipped = VK_TRUE;
		swapChainCreateInfo.oldSwapchain = VK_NULL_HANDLE;


		// TODO: Multiple Queues?
		// Queue family setup.
		uint32_t familyIndices[]
		{
			_device.queueMgr.graphics[0].GetFamilyIndex(),
			_device.queueMgr.present[0].GetFamilyIndex(),
		};

		if (_device.queueMgr.present[0].IsValid() && familyIndices[0] != familyIndices[1]) // Graphic and present familiy are different.
		{
			swapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			swapChainCreateInfo.queueFamilyIndexCount = sizeof(familyIndices) / sizeof(uint32_t);
			swapChainCreateInfo.pQueueFamilyIndices = familyIndices;
		}


		SA_VK_ASSERT(vkCreateSwapchainKHR(_device, &swapChainCreateInfo, nullptr, &mHandle), L"Failed to create swap chain!");

		SA_LOG(L"Swap chain [" << mHandle << L"] created.", Infos, SA/Engine/Render/Vulkan);
	}
	
	void SwapChain::DestroySwapChainKHR(const Device& _device)
	{
		SA_ASSERT(Default, SA/Engine/Render/Vulkan, mHandle != VK_NULL_HANDLE, L"Destroy a null swapchain!");

		vkDestroySwapchainKHR(_device, mHandle, nullptr);

		SA_LOG(L"Swap chain [" << mHandle << L"] destroyed.", Infos, SA/Engine/Render/Vulkan);

		mHandle = VK_NULL_HANDLE;
	}

	
	void SwapChain::CreateSynchronisation(const Device& _device)
	{
		VkSemaphoreCreateInfo semaphoreCreateInfo{};
		semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		semaphoreCreateInfo.pNext = nullptr;
		semaphoreCreateInfo.flags = 0u;

		VkFenceCreateInfo fenceCreateInfo{};
		fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceCreateInfo.pNext = nullptr;
		fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		mFramesSynch.resize(mImageNum);

		for (auto it = mFramesSynch.begin(); it != mFramesSynch.end(); ++it)
		{
			SA_VK_ASSERT(vkCreateSemaphore(_device, &semaphoreCreateInfo, nullptr, &it->acquireSemaphore), L"Failed to create acquire semaphore!");
			SA_VK_ASSERT(vkCreateSemaphore(_device, &semaphoreCreateInfo, nullptr, &it->presentSemaphore), L"Failed to create present semaphore!");
			SA_VK_ASSERT(vkCreateFence(_device, &fenceCreateInfo, nullptr, &it->fence), L"Failed to create fence!");
		}

		SA_LOG(L"Swap chain synchronisation created.", Infos, SA/Engine/Render/Vulkan);
	}
	
	void SwapChain::DestroySynchronisation(const Device& _device)
	{
		for (auto it = mFramesSynch.begin(); it != mFramesSynch.end(); ++it)
		{
			vkDestroySemaphore(_device, it->acquireSemaphore, nullptr);
			vkDestroySemaphore(_device, it->presentSemaphore, nullptr);
			vkDestroyFence(_device, it->fence, nullptr);
		}

		mFramesSynch.clear();

		SA_LOG(L"Swap chain synchronisation destroyed.", Infos, SA/Engine/Render/Vulkan);
	}


	void SwapChain::Create(const Device& _device, const Surface& _surface)
	{
		CreateSwapChainKHR(_device, _surface);
		CreateSynchronisation(_device);
	}

	void SwapChain::Destroy(const Device& _device)
	{
		DestroySynchronisation(_device);
		DestroySwapChainKHR(_device);
	}
}
