// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_BUFFER_GUARD
#define SAPPHIRE_RENDER_VK_BUFFER_GUARD

#include <SA/Render/Vulkan/Buffers/VkBufferBase.hpp>

namespace Sa::Vk
{
	class ResourceInitializer;
	
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
			VkBufferUsageFlags _usage,
			uint64 _size,
			const void* _data);

		void UpdateData(const Device& _device, const void* _data, uint64 _size, uint64 _offset = 0u);


		static Buffer& CreateStaging(const Device& _device, ResourceInitializer& _init, const void* _data, uint64 _size);
	};
}

#endif // GUARD
