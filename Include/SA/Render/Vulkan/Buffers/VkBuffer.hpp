// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_BUFFER_GUARD
#define SAPPHIRE_RENDER_VK_BUFFER_GUARD

#include <SA/Render/Vulkan/Buffers/VkBufferBase.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class Buffer : public BufferBase
	{
	public:
		class Deleter
		{
			const Device& mDevice;

		public:
			Deleter(const Device& _device) noexcept;

			void operator()(Buffer& _buffer);
		};


		void Create(const Device& _device,
			uint64 _size,
			VkBufferUsageFlags _usage,
			VkMemoryPropertyFlags _properties,
			const void* _data = nullptr);

		void UpdateData(const Device& _device, const void* _data, uint64 _size, uint64 _offset = 0);
	};
}

#endif

#endif // GUARD
