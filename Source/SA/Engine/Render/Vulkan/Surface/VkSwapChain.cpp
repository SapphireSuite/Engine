// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Surface/VkSwapChain.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>

#include <Render/Vulkan/Device/VkDevice.hpp>

#include <Render/Vulkan/Surface/VkSurface.hpp>
#include <Render/Vulkan/Surface/VkSurfaceSupportDetails.hpp>

namespace Sa::Vk
{
	Vec2ui SwapChain::GetExtent() const
	{
		return mExtent;
	}
	
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

		mFrames.resize(mImageNum);


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

		for (auto it = mFrames.begin(); it != mFrames.end(); ++it)
		{
			SA_VK_ASSERT(vkCreateSemaphore(_device, &semaphoreCreateInfo, nullptr, &it->sync.acquireSemaphore), L"Failed to create acquire semaphore!");
			SA_VK_ASSERT(vkCreateSemaphore(_device, &semaphoreCreateInfo, nullptr, &it->sync.presentSemaphore), L"Failed to create present semaphore!");
			SA_VK_ASSERT(vkCreateFence(_device, &fenceCreateInfo, nullptr, &it->sync.fence), L"Failed to create fence!");
		}

		SA_LOG(L"Swap chain synchronisation created.", Infos, SA/Engine/Render/Vulkan);
	}
	
	void SwapChain::DestroySynchronisation(const Device& _device)
	{
		for (auto it = mFrames.begin(); it != mFrames.end(); ++it)
		{
			vkDestroySemaphore(_device, it->sync.acquireSemaphore, nullptr);
			vkDestroySemaphore(_device, it->sync.presentSemaphore, nullptr);
			vkDestroyFence(_device, it->sync.fence, nullptr);
		}

		SA_LOG(L"Swap chain synchronisation destroyed.", Infos, SA/Engine/Render/Vulkan);
	}


	void SwapChain::CreateCommandBuffers(const Device& _device)
	{
		// TODO: Clean.
		mCmdPool.Create(_device, _device.queueMgr.graphics.GetQueue(0).GetFamilyIndex());

		for (auto it = mFrames.begin(); it != mFrames.end(); ++it)
			it->cmd = mCmdPool.Allocate(_device);

		SA_LOG(L"Swap chain cmd created.", Infos, SA/Engine/Render/Vulkan);
	}
	
	void SwapChain::DestroyCommandBuffers(const Device& _device)
	{
		mCmdPool.Destroy(_device);
		
		SA_LOG(L"Swap chain cmd destroyed.", Infos, SA/Engine/Render/Vulkan);
	}


	void SwapChain::Create(const Device& _device, const Surface& _surface)
	{
		CreateSwapChainKHR(_device, _surface);
		CreateSynchronisation(_device);
		CreateCommandBuffers(_device);
	}

	void SwapChain::Destroy(const Device& _device)
	{
		if(!mFrames.empty() && mFrames[0].fBuff != VK_NULL_HANDLE)
		{
			SA_LOG(L"Self destroy SwapChain's Frame Buffers on destroy.", Warning, SA/Engine/Render/Vulkan);

			DestroyFrameBuffers(_device);
		}

		DestroySynchronisation(_device);
		DestroySwapChainKHR(_device);
		DestroyCommandBuffers(_device);
	}


	void SwapChain::CreateFrameBuffers(const Device& _device,
		const RenderPass& _renderPass,
		const RenderPassDescriptor& _renderPassDesc)
	{
		std::vector<VkImage> swapChainImages(mImageNum);
		vkGetSwapchainImagesKHR(_device, mHandle, &mImageNum, swapChainImages.data());

		for (uint32_t i = 0u; i < mImageNum; ++i)
			mFrames[i].fBuff.Create(_device, _renderPass, _renderPassDesc, mExtent, swapChainImages[i]);

		SA_LOG(L"SwapChain FrameBuffers created.", Infos, SA/Engine/Render/Vulkan);
	}

	void SwapChain::DestroyFrameBuffers(const Device& _device)
	{
		for (auto it = mFrames.begin(); it != mFrames.end(); ++it)
			it->fBuff.Destroy(_device);

		SA_LOG(L"SwapChain FrameBuffers destroyed.", Infos, SA/Engine/Render/Vulkan);
	}


	Frame& SwapChain::Begin(const Device& _device)
	{
		SwapFrame& frame = mFrames[mFrameIndex];


		// Wait current Fence.
		vkWaitForFences(_device, 1, &frame.sync.fence, true, UINT64_MAX);

		// Reset current Fence.
		vkResetFences(_device, 1, &frame.sync.fence);


		SA_VK_ASSERT(vkAcquireNextImageKHR(_device, mHandle, UINT64_MAX, frame.sync.acquireSemaphore, VK_NULL_HANDLE, &mImageIndex),
			L"Failed to aquire next image!");


		frame.cmd.Begin();

		return frame;
	}
	
	void SwapChain::End(const Device& _device)
	{
		SwapFrame& frame = mFrames[mFrameIndex];

		frame.cmd.End();


		// Submit graphics.
		const VkPipelineStageFlags waitStages = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.pNext = nullptr;
		submitInfo.waitSemaphoreCount = 1u;
		submitInfo.pWaitSemaphores = &frame.sync.acquireSemaphore;
		submitInfo.pWaitDstStageMask = &waitStages;
		submitInfo.commandBufferCount = 1u;
		submitInfo.pCommandBuffers = reinterpret_cast<const VkCommandBuffer*>(&frame.cmd); // Warning: Unsafe.
		submitInfo.signalSemaphoreCount = 1u;
		submitInfo.pSignalSemaphores = &frame.sync.presentSemaphore;

		SA_VK_ASSERT(vkQueueSubmit(_device.queueMgr.graphics.GetQueue(0), 1, &submitInfo, frame.sync.fence),
			L"Failed to submit graphics queue!");


		// Submit present.
		VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.pNext = nullptr;
		presentInfo.waitSemaphoreCount = 1u;
		presentInfo.pWaitSemaphores = &frame.sync.presentSemaphore;
		presentInfo.swapchainCount = 1u;
		presentInfo.pSwapchains = &mHandle;
		presentInfo.pImageIndices = &mImageIndex;
		presentInfo.pResults = nullptr;

		SA_VK_ASSERT(vkQueuePresentKHR(_device.queueMgr.present.GetQueue(0), &presentInfo),
			L"Failed to submit present queue!");


		// Increment next frame.
		mFrameIndex = (mFrameIndex + 1) % mImageNum;
	}
}
