// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_GPU_BUFFER_LIBRARY_GUARD
#define SAPPHIRE_ENGINE_VK_GPU_BUFFER_LIBRARY_GUARD

#include <cstdint>

#include <SA/Support/API/Vulkan.hpp>

namespace SA::VK
{
	class Device;
	class ObjectBuffer;
	class ResourceInitializer;

	class GPUBufferLibrary
	{
	public:
		~GPUBufferLibrary() = delete;

		static constexpr VkMemoryPropertyFlags defaultProperties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

		static void CopyData(ResourceInitializer& _init, const ObjectBuffer& _src, ObjectBuffer& _dst);
		static void CopyData(const Device& _device,
			ResourceInitializer& _init,
			const void* _src,
			ObjectBuffer& _dst,
			uint64_t _size,
			uint64_t _dstOffset = 0u);
	};
}

#endif // GUARD
