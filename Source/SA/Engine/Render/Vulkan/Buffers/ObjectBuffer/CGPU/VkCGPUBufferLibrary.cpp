// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <cstring>

#include <Render/Vulkan/Buffers/ObjectBuffer/CGPU/VkCGPUBufferLibrary.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>
#include <Render/Vulkan/Device/VkDevice.hpp>
#include <Render/Vulkan/Buffers/ObjectBuffer/VkObjectBuffer.hpp>

namespace SA::VK
{
	void CGPUBufferLibrary::CopyData(const Device& _device, ObjectBuffer& _buffer, const void* _src, uint64_t _size, uint64_t _offset)
	{
		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, _src, L"Source nullptr! Use ResetData instead!");

		void* bufferData = nullptr;

		SA_VK_ASSERT(vkMapMemory(_device, _buffer, _offset, _size, 0, &bufferData), L"Fail to map memory");

		std::memcpy(bufferData, _src, _size);

		vkUnmapMemory(_device, _buffer);
	}

	void CGPUBufferLibrary::MoveData(const Device& _device, ObjectBuffer& _buffer, const void* _src, uint64_t _size, uint64_t _offset)
	{
		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, _src, L"Source nullptr! Use ResetData instead!");

		void* bufferData = nullptr;

		SA_VK_ASSERT(vkMapMemory(_device, _buffer, _offset, _size, 0, &bufferData), L"Fail to map memory");

		std::memmove(bufferData, _src, _size);

		vkUnmapMemory(_device, _buffer);
	}

	void CGPUBufferLibrary::ResetData(const Device& _device, ObjectBuffer& _buffer, uint64_t _size, uint64_t _offset)
	{
		void* bufferData = nullptr;

		SA_VK_ASSERT(vkMapMemory(_device, _buffer, _offset, _size, 0, &bufferData), L"Fail to map memory");

		std::memset(bufferData, 0, _size);

		vkUnmapMemory(_device, _buffer);
	}
}
