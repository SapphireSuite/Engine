// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/VkResourceContext.hpp>

#include <Render/Vulkan/Device/VkDevice.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	void ResourceContext::Create(const ARenderDevice* _device)
	{
		mDevice = _device->AsPtr<Device>();

		// TODO: Clean queue.
		mCmdPool.Create(*mDevice, mDevice->queueMgr.transfer.GetQueue(0).GetFamilyIndex());

		cmd = mCmdPool.Allocate(*mDevice);
		cmd.Begin();
	}

	void ResourceContext::Destroy()
	{
		mCmdPool.Destroy(*mDevice);
		mDevice = nullptr;

		resHolder.FreeAll();
	}


	void ResourceContext::Submit()
	{
		cmd.End();


		// Submit commands.
		VkCommandBuffer vkCmd = cmd;
		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.pNext = nullptr;
		submitInfo.waitSemaphoreCount = 0u;
		submitInfo.pWaitSemaphores = nullptr;
		submitInfo.pWaitDstStageMask = nullptr;
		submitInfo.commandBufferCount = 1u;
		submitInfo.pCommandBuffers = &vkCmd;
		submitInfo.signalSemaphoreCount = 0u;
		submitInfo.pSignalSemaphores = nullptr;

		// TODO: Clean queue.
		vkQueueSubmit(mDevice->queueMgr.transfer.GetQueue(0), 1, &submitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(mDevice->queueMgr.transfer.GetQueue(0));

		resHolder.FreeAll();


		// Ready for new submit.
		cmd.Begin();
	}
}

#endif
