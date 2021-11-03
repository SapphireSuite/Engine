// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_GPU_BUFFER_GUARD
#define SAPPHIRE_RENDER_VK_GPU_BUFFER_GUARD

#include <SA/Render/Vulkan/Buffers/VkBuffer.hpp>

namespace Sa::Vk
{
	class ResourceInitializer;

	class GPUBuffer : public Buffer
	{
		using Buffer::Create;

	public:
		void Create(const Device& _device,
			VkBufferUsageFlags _usage,
			uint64 _size);

		void Create(const Device& _device,
			ResourceInitializer& _init,
			VkBufferUsageFlags _usage,
			uint64 _size,
			const void* _data);

		void UpdateData(const Device& _device, ResourceInitializer& _init, const void* _data, uint64 _size, uint64 _offset = 0);
	};
}

#endif // GUARD
