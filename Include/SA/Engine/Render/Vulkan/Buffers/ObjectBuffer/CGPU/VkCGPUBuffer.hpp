// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma	once

#ifndef SAPPHIRE_ENGINE_VK_CGPU_BUFFER_GUARD
#define SAPPHIRE_ENGINE_VK_CGPU_BUFFER_GUARD

#include <SA/Engine/Render/Vulkan/Buffers/ObjectBuffer/VkObjectBuffer.hpp>

namespace SA::VK
{
	class ResourceInitializer;

	class CGPUBuffer : public ObjectBuffer
	{
		using ObjectBuffer::Create;

	public:
		void Create(const Device& _device,
			VkBufferUsageFlags _usage,
			uint64_t _size,
			const void* _data = nullptr);

		void UpdateData(const Device& _device, const void* _data, uint64_t _size, uint64_t _offset = 0u);

		static CGPUBuffer& CreateStaging(const Device& _device, ResourceInitializer& _init, const void* _data, uint64_t _size);
	};
}

#endif // GUARD
