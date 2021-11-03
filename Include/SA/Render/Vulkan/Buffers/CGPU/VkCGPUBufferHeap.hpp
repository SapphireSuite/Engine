// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_CGPU_BUFFER_HEAP_GUARD
#define SAPPHIRE_RENDER_VK_CGPU_BUFFER_HEAP_GUARD

#include <SA/Render/Vulkan/Buffers/VkBufferHeap.hpp>

namespace Sa::Vk
{
	class CGPUBufferHeap : public BufferHeap
	{
		using BufferHeap::Create;

		void ReallocBuffer(const Device& _device, uint64 _newCapacity, ResourceInitializer* _init) override final;

	public:
		void Create(const Device& _device,
			VkBufferUsageFlags _usage,
			uint64 _size);

		const MetaData* Allocate(const Device& _device, const void* _data, uint64 _size);
	};
}

#endif // GUARD
