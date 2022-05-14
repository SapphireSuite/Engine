// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_CGPU_BUFFER_LIBRARY_GUARD
#define SAPPHIRE_ENGINE_VK_CGPU_BUFFER_LIBRARY_GUARD

#include <cstdint>

#include <SA/Support/API/Vulkan.hpp>

namespace SA::VK
{
	class Device;
	class ObjectBuffer;

	class CGPUBufferLibrary
	{
	public:
		~CGPUBufferLibrary() = delete;

		static constexpr VkMemoryPropertyFlags defaultProperties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

		static void CopyData(const Device& _device, ObjectBuffer& _buffer, const void* _src, uint64_t _size, uint64_t _offset = 0u);
		static void MoveData(const Device& _device, ObjectBuffer& _buffer, const void* _src, uint64_t _size, uint64_t _offset = 0u);
		static void ResetData(const Device& _device, ObjectBuffer& _buffer, uint64_t _size, uint64_t _offset = 0u);
	};
}

#endif // GUARD
