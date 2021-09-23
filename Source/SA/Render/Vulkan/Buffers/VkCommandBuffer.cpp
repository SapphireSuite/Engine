// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Buffers/VkCommandBuffer.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	void CommandBuffer::Begin()
	{
		vkResetCommandBuffer(mHandle, VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);

		// Start Command buffer record.
		VkCommandBufferBeginInfo commandBufferBeginInfo{};
		commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		commandBufferBeginInfo.pNext = nullptr;
		commandBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		commandBufferBeginInfo.pInheritanceInfo = nullptr;

		SA_VK_ASSERT(vkBeginCommandBuffer(mHandle, &commandBufferBeginInfo), L"Failed to begin command buffer!");
	}

	void CommandBuffer::End()
	{
		// End Command buffer record.
		SA_VK_ASSERT(vkEndCommandBuffer(mHandle), L"Failed to end command buffer!");
	}


	CommandBuffer::operator VkCommandBuffer() const
	{
		return mHandle;
	}
}

#endif
