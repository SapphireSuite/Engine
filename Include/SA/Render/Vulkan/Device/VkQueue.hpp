// Copyright 2021 Sapphire development team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_QUEUE_GUARD
#define SAPPHIRE_RENDER_VK_QUEUE_GUARD

#include <SA/Core/Support/API/Vulkan.hpp>

#include <SA/Core/Types/Int.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class Device;

	class Queue
	{
		VkQueue mHandle = VK_NULL_HANDLE;

		uint32 mFamilyIndex = ~uint32();

	public:
		bool IsValid() const noexcept;
		uint32 GetFamilyIndex() const noexcept;

		void Create(const Device& _device, uint32 _queueFamilyIndex, uint32 _queueIndex = 0);
		void Destroy(const Device& _device);
	};
}

#endif

#endif // GUARD
