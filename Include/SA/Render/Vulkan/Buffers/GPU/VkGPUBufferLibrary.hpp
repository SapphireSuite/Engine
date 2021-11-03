// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_GPU_BUFFER_LIBRARY_GUARD
#define SAPPHIRE_RENDER_VK_GPU_BUFFER_LIBRARY_GUARD

#include <SA/Core/Types/Int.hpp>

namespace Sa::Vk
{
	class Device;
	class Buffer;
	class ResourceInitializer;

	class GPUBufferLibrary
	{
	public:
		~GPUBufferLibrary() = delete;

		static void CopyData(const Device& _device, Buffer& _buffer, ResourceInitializer& _init, const void* _src, uint64 _size, uint64 _offset = 0u);
	};
}

#endif // GUARD
