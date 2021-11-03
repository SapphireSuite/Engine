// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma	once

#ifndef SAPPHIRE_RENDER_VK_CGPU_BUFFER_GUARD
#define SAPPHIRE_RENDER_VK_CGPU_BUFFER_GUARD

#include <SA/Render/Vulkan/Buffers/VkBuffer.hpp>

namespace Sa::Vk
{
	class CGPUBuffer : public Buffer
	{
		using Buffer::Create;

	public:
		void Create(const Device& _device,
			VkBufferUsageFlags _usage,
			uint64 _size,
			const void* _data = nullptr);

		void UpdateData(const Device& _device, const void* _data, uint64 _size, uint64 _offset = 0u);
	};
}

#endif // GUARD
