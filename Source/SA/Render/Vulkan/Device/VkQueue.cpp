// Copyright 2021 Sapphire development team. All Rights Reserved.

#include <Render/Vulkan/Device/VkQueue.hpp>

#include <Render/Vulkan/Device/VkDevice.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	bool Queue::IsValid() const noexcept
	{
		return mHandle;
	}

	void Queue::Create(const Device& _device, uint32 _queueFamilyIndex, uint32 _queueIndex)
	{
		SA_ASSERT(Default, SA/Render/Vulkan, _queueFamilyIndex != ~uint32(), L"Invalid queue family index: -1");

		vkGetDeviceQueue(_device, _queueFamilyIndex, _queueIndex, &mHandle);

		SA_LOG(L"Queue family [" << _queueFamilyIndex << L"] index [" << _queueIndex << "] created", Infos, SA/Render/Vulkan);
	}

	void Queue::Destroy(const Device& _device)
	{
		mHandle = VK_NULL_HANDLE;

		SA_LOG(L"Queue destroyed", Infos, SA/Render/Vulkan);
	}
}

#endif