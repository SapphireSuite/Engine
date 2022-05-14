// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Device/Command/VkCommandPool.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>

#include <Render/Vulkan/Device/VkDevice.hpp>

namespace SA::VK
{
	void CommandPool::Create(const Device& _device, uint32_t _queueFamilyIndex)
	{
		SA_ASSERT(Default, SA/Render/Vulkan, mHandle == VK_NULL_HANDLE, L"Command pool already created!");

		VkCommandPoolCreateInfo commandPoolCreateInfo{};
		commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		commandPoolCreateInfo.pNext = nullptr;
		commandPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		commandPoolCreateInfo.queueFamilyIndex = _queueFamilyIndex;

		SA_VK_ASSERT(vkCreateCommandPool(_device, &commandPoolCreateInfo, nullptr, &mHandle), L"Failed to create command pool!");

		SA_LOG(L"Command pool created.", Infos, SA/Render/Vulkan);
	}

	void CommandPool::Destroy(const Device& _device)
	{
		SA_ASSERT(Default, SA/Render/Vulkan, mHandle != VK_NULL_HANDLE, L"Command pool nullptr! Try to destroy a null command pool.")

		vkDestroyCommandPool(_device, mHandle, nullptr);

		mHandle = VK_NULL_HANDLE;

		SA_LOG(L"Command pool destroyed.", Infos, SA/Render/Vulkan);
	}


	void CommandPool::Reset(const Device& _device)
	{
		SA_ASSERT(Default, SA/Render/Vulkan, mHandle != VK_NULL_HANDLE, L"Command pool nullptr! Try to reset a null command pool.")

		vkResetCommandPool(_device, mHandle, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);
	}


	CommandBuffer CommandPool::Allocate(const Device& _device, VkCommandBufferLevel _level)
	{
		CommandBuffer result;

		VkCommandBufferAllocateInfo commandBufferAllocInfo{};
		commandBufferAllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		commandBufferAllocInfo.pNext = nullptr;
		commandBufferAllocInfo.commandPool = mHandle;
		commandBufferAllocInfo.level = _level;
		commandBufferAllocInfo.commandBufferCount = 1u;

		SA_VK_ASSERT(vkAllocateCommandBuffers(_device, &commandBufferAllocInfo, &result.mHandle),
			L"Failed to allocate command buffers!");

		return result;
	}

	std::vector<CommandBuffer> CommandPool::AllocateMultiple(const Device& _device, uint32_t _num, VkCommandBufferLevel _level)
	{
		std::vector<CommandBuffer> result{ _num };
		std::vector<VkCommandBuffer> vkCommandBuffers{ _num };

		VkCommandBufferAllocateInfo commandBufferAllocInfo{};
		commandBufferAllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		commandBufferAllocInfo.pNext = nullptr;
		commandBufferAllocInfo.commandPool = mHandle;
		commandBufferAllocInfo.level = _level;
		commandBufferAllocInfo.commandBufferCount = _num;

		SA_VK_ASSERT(vkAllocateCommandBuffers(_device, &commandBufferAllocInfo, vkCommandBuffers.data()),
			L"Failed to allocate command buffers!");

		for (uint32_t i = 0; i < _num; ++i)
			result[i].mHandle = vkCommandBuffers[i];

		return result;
	}


	void CommandPool::Free(const Device& _device, CommandBuffer& _buffer)
	{
		SA_ASSERT(Default, SA/Render/Vulkan, _buffer != VK_NULL_HANDLE, L"Destroy a null command buffer!");

		vkFreeCommandBuffers(_device, mHandle, 1u, &_buffer.mHandle);

		_buffer.mHandle = VK_NULL_HANDLE;
	}

	void CommandPool::FreeMultiple(const Device& _device, std::vector<CommandBuffer>& _buffers)
	{
		const uint32_t num = (uint32_t)_buffers.size();

		std::vector<VkCommandBuffer> vkCommandBuffers;
		vkCommandBuffers.resize(num);

		for (uint32_t i = 0; i < num; ++i)
		{
			vkCommandBuffers[i] = _buffers[i].mHandle;
			_buffers[i].mHandle = VK_NULL_HANDLE;
		}

		vkFreeCommandBuffers(_device, mHandle, num, vkCommandBuffers.data());
	}


	CommandPool::operator VkCommandPool() const
	{
		return mHandle;
	}
}
