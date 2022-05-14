// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_GPU_BUFFER_GUARD
#define SAPPHIRE_ENGINE_VK_GPU_BUFFER_GUARD

#include <SA/Engine/Render/Vulkan/Buffers/ObjectBuffer/VkObjectBuffer.hpp>

namespace SA::VK
{
	class ResourceInitializer;

	class GPUBuffer : public ObjectBuffer
	{
		using ObjectBuffer::Create;

	public:
		void Create(const Device& _device,
			VkBufferUsageFlags _usage,
			uint64_t _size);

		void Create(const Device& _device,
			ResourceInitializer& _init,
			VkBufferUsageFlags _usage,
			uint64_t _size,
			const void* _data);

		void UpdateData(const Device& _device, ResourceInitializer& _init, const void* _data, uint64_t _size, uint64_t _offset = 0);
	};
}

#endif // GUARD
