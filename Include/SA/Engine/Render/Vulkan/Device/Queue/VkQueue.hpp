// Copyright 2022 Sapphire development team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_QUEUE_GUARD
#define SAPPHIRE_ENGINE_VK_QUEUE_GUARD

#include <SA/Support/API/Vulkan.hpp>

namespace Sa::Vk
{
	class Device;

	class Queue
	{
		VkQueue mHandle = VK_NULL_HANDLE;

		uint32_t mFamilyIndex = ~uint32_t();

	public:
		bool IsValid() const noexcept;
		uint32_t GetFamilyIndex() const noexcept;

		void Create(const Device& _device, uint32_t _queueFamilyIndex, uint32_t _queueIndex = 0);
		void Destroy(const Device& _device);

		operator VkQueue() const;
	};
}

#endif // GUARD
