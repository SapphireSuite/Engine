// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_CGPU_BUFFER_LIBRARY_GUARD
#define SAPPHIRE_RENDER_VK_CGPU_BUFFER_LIBRARY_GUARD

#include <SA/Core/Types/Int.hpp>

namespace Sa::Vk
{
	class Device;
	class Buffer;

	class CGPUBufferLibrary
	{
	public:
		~CGPUBufferLibrary() = delete;

		static void CopyData(const Device& _device, Buffer& _buffer, const void* _src, uint64 _size, uint64 _offset = 0u);
		static void MoveData(const Device& _device, Buffer& _buffer, const void* _src, uint64 _size, uint64 _offset = 0u);
		static void ResetData(const Device& _device, Buffer& _buffer, uint64 _size, uint64 _offset = 0u);
	};
}

#endif // GUARD
