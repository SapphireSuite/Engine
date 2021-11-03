// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_GPU_BUFFER_LIBRARY_GUARD
#define SAPPHIRE_RENDER_VK_GPU_BUFFER_LIBRARY_GUARD

#include <SA/Core/Types/Int.hpp>

#include <SA/Core/Support/API/Vulkan.hpp>

namespace Sa::Vk
{
	class Device;
	class Buffer;
	class ResourceInitializer;

	class GPUBufferLibrary
	{
	public:
		~GPUBufferLibrary() = delete;

		static constexpr VkMemoryPropertyFlags defaultProperties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

		static void CopyData(ResourceInitializer& _init, const Buffer& _src, Buffer& _dst);
		static void CopyData(const Device& _device,
			ResourceInitializer& _init,
			const void* _src,
			Buffer& _dst,
			uint64 _size,
			uint64 _dstOffset = 0u);
	};
}

#endif // GUARD
