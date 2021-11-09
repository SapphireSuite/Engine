// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_BUFFER_GUARD
#define SAPPHIRE_RENDER_VK_BUFFER_GUARD

#include <SA/Core/Types/Int.hpp>

#include <SA/Core/Support/API/Vulkan.hpp>

namespace Sa::Vk
{
	class Device;
	class CommandBuffer;

	class Buffer
	{
	protected:
		VkBuffer mHandle = VK_NULL_HANDLE;
		VkDeviceMemory mDeviceMemory = VK_NULL_HANDLE;

		uint64 mDeviceSize = 0u;

	public:
		class Deleter
		{
			const Device& mDevice;

		public:
			Deleter(const Device& _device) noexcept;

			void operator()(Buffer& _buffer) const;
		};


		Buffer() = default;
		Buffer(Buffer&& _other) noexcept;


		bool IsValid() const noexcept;
		uint64 GetCapacity() const noexcept;

		virtual void Create(const Device& _device,
			uint64 _size, VkBufferUsageFlags _usage,
			VkMemoryPropertyFlags _properties);
		virtual void Destroy(const Device& _device);


		VkDescriptorBufferInfo CreateDescriptorBufferInfo() const noexcept;

		void BindAsVertexBuffer(CommandBuffer& _cmd) const;
		void BindAsIndexBuffer(CommandBuffer& _cmd) const;

		static uint32 FindMemoryType(const Device& _device, uint32 _typeFilter, VkMemoryPropertyFlags _properties);


		Buffer& operator=(Buffer&& _rhs);

		operator VkBuffer() const noexcept;
		operator VkDeviceMemory() const noexcept;

		bool operator==(const Buffer& _rhs) const noexcept;
	};
}

#endif // GUARD
