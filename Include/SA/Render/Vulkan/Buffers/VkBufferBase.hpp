// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_BUFFER_BASE_GUARD
#define SAPPHIRE_RENDER_VK_BUFFER_BASE_GUARD

#include <SA/Core/Types/Int.hpp>

#include <SA/Core/Support/API/Vulkan.hpp>

#include <SA/Render/Base/Buffers/IUniformBuffer.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class Device;

	class BufferBase : public IUniformBuffer
	{
	protected:
		VkBuffer mHandle = VK_NULL_HANDLE;
		VkDeviceMemory mDeviceMemory = VK_NULL_HANDLE;

		uint64 mDeviceSize = 0u;

		void Create_Internal(const Device& _device,
			uint64 _size, VkBufferUsageFlags _usage,
			VkMemoryPropertyFlags _properties);

	public:
		bool IsValid() const noexcept;

		void Destroy(const Device& _device);

		VkDescriptorBufferInfo CreateDescriptorBufferInfo() const noexcept;

		static uint32 FindMemoryType(const Device& _device, uint32 _typeFilter, VkMemoryPropertyFlags _properties);

		operator VkBuffer() const noexcept;
		operator VkDeviceMemory() const noexcept;
	};
}

#endif

#endif // GUARD
