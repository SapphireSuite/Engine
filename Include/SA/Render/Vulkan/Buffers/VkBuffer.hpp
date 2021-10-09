// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_BUFFER_GUARD
#define SAPPHIRE_RENDER_VK_BUFFER_GUARD

#include <SA/Render/Base/Buffers/ARenderBuffer.hpp>
#include <SA/Render/Vulkan/Buffers/VkBufferHandle.hpp>
#include <SA/Render/Vulkan/Buffers/IVkBufferBinding.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class ResourceInitializer;
	
	class Buffer : public ARenderBuffer, public IBufferBinding
	{
		BufferHandle mHandle;

	public:
		bool IsValid() const noexcept override final;


		void Create(const ARenderDevice* _device,
			RenderBufferType _type,
			uint64 _size,
			const void* _data) override final;

		void Destroy(const ARenderDevice* _device) override final;


		void UpdateData(const ARenderDevice* _device, const void* _data, uint64 _size, uint64 _offset = 0u) override final;


		VkDescriptorBufferInfo CreateDescriptorBufferInfo() const noexcept override final;


		static Buffer& CreateStaging(ResourceInitializer& _init, const void* _data, uint64 _size);


		operator VkBuffer() const noexcept;
	};
}

#endif

#endif // GUARD
