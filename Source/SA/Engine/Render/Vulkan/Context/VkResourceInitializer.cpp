// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Context/VkResourceInitializer.hpp>

#include <SA/Collections/Debug>

#include <Render/Vulkan/Device/VkDevice.hpp>

namespace SA::VK
{
	void ResourceInitializer::Create(const Device& _device)
	{
		ARenderResourceInitializer::Create();

		// TODO: Clean queue.
		mCmdPool.Create(_device, _device.queueMgr.transfer.GetQueue(0).GetFamilyIndex());

		cmd = mCmdPool.Allocate(_device);
		cmd.Begin();
		
		SA_LOG(L"Render Resource Initializer created.", Infos, SA/Engine/Render/Vulkan);
	}
	
	void ResourceInitializer::Destroy(const Device& _device)
	{
		ARenderResourceInitializer::Destroy();

		mCmdPool.Destroy(_device);

		resHolder.FreeAll();
		
		SA_LOG(L"Render Resource Initializer destroyed.", Infos, SA/Engine/Render/Vulkan);
	}

	
	void ResourceInitializer::Submit(const Device& _device)
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
		vkQueueSubmit(_device.queueMgr.transfer.GetQueue(0), 1, &submitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(_device.queueMgr.transfer.GetQueue(0));

		resHolder.FreeAll();


		// Ready for new submit.
		cmd.Begin();
	}
}
