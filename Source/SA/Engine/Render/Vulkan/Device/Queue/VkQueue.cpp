// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Device/Queue/VkQueue.hpp>

#include <SA/Collections/Debug>

#include <Render/Vulkan/Device/VkDevice.hpp>

namespace Sa::Vk
{
	bool Queue::IsValid() const noexcept
	{
		return mHandle;
	}

	uint32_t Queue::GetFamilyIndex() const noexcept
	{
		return mFamilyIndex;
	}


	void Queue::Create(const Device& _device, uint32_t _queueFamilyIndex, uint32_t _queueIndex)
	{
		SA_ASSERT(Default, SA/Engine/Render/Vulkan, _queueFamilyIndex != ~uint32_t(), L"Invalid queue family index: -1");

		mFamilyIndex = _queueFamilyIndex;
		vkGetDeviceQueue(_device, _queueFamilyIndex, _queueIndex, &mHandle);

		SA_LOG(L"Queue family [" << _queueFamilyIndex << L"] index [" << _queueIndex << "] created", Infos, SA/Engine/Render/Vulkan);
	}

	void Queue::Destroy(const Device& _device)
	{
		(void)_device;

		mHandle = VK_NULL_HANDLE;
		mFamilyIndex = ~uint32_t();

		SA_LOG(L"Queue destroyed", Infos, SA/Engine/Render/Vulkan);
	}


	Queue::operator VkQueue() const
	{
		return mHandle;
	}
}
