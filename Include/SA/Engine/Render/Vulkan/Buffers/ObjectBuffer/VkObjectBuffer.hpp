// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_OBJECT_BUFFER_GUARD
#define SAPPHIRE_ENGINE_VK_OBJECT_BUFFER_GUARD

#include <SA/Engine/Render/Vulkan/Buffers/VkABuffer.hpp>

namespace SA::VK
{
	class ObjectBuffer : public ABuffer
	{
	protected:
		VkBuffer mHandle = VK_NULL_HANDLE;
		VkDeviceMemory mDeviceMemory = VK_NULL_HANDLE;

		uint64_t mDeviceSize = 0u;

		VkBufferUsageFlags mUsage = 0u;

	public:
		class Deleter
		{
			const Device& mDevice;

		public:
			Deleter(const Device& _device) noexcept;

			void operator()(ObjectBuffer& _buffer) const;
		};


		ObjectBuffer() = default;
		ObjectBuffer(ObjectBuffer&& _other) noexcept;


		bool IsValid() const noexcept;
		uint64_t GetCapacity() const noexcept;

		VkBufferUsageFlags GetUsage() const noexcept;
		VkDescriptorType GetDescriptorType() const noexcept;


		virtual void Create(const Device& _device,
			uint64_t _size, VkBufferUsageFlags _usage,
			VkMemoryPropertyFlags _properties);
		virtual void Destroy(const Device& _device);


		VkDescriptorBufferInfo CreateDescriptorBufferInfo() const noexcept;

		operator VkBuffer() const noexcept;
		operator VkDeviceMemory() const noexcept;
	};
}

#endif // GUARD
