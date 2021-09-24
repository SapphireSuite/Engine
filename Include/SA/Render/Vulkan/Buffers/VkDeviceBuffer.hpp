// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_DEVICE_BUFFER_GUARD
#define SAPPHIRE_RENDER_VK_DEVICE_BUFFER_GUARD

#include <SA/Render/Vulkan/VkResourceInitializer.hpp>
#include <SA/Render/Vulkan/Buffers/VkBufferBase.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class DeviceBuffer : public BufferBase
	{
	public:
		void Create(const Device& _device,
			uint64 _size,
			VkBufferUsageFlags _usage);

		void Create(ResourceInitializer* _init,
			uint64 _size,
			VkBufferUsageFlags _usage,
			const void* _data);

		void UpdateData(ResourceInitializer* _init, const void* _data, uint64 _size, uint64 _offset = 0);
	};
}

#endif

#endif // GUARD
