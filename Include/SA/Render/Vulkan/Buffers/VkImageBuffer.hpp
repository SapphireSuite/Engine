// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_IMAGE_BUFFER_GUARD
#define SAPPHIRE_RENDER_VK_IMAGE_BUFFER_GUARD

#include <SA/Core/Types/Variadics/ResourceHolder.hpp>

#include <SA/Render/Vulkan/Buffers/VkImageBufferCreateInfos.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class Device;
	class CommandBuffer;

	class ImageBuffer
	{
		VkImage mImage = VK_NULL_HANDLE;
		VkImageView mImageView = VK_NULL_HANDLE;
		VkDeviceMemory mImageMemory = VK_NULL_HANDLE;

	public:
		struct TransitionInfos
		{
			VkImageLayout oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			VkImageLayout newLayout = VK_IMAGE_LAYOUT_UNDEFINED;

			uint32 mipLevels = 1u;
			ImageType imageType = ImageType::Image2D;

			VkImageAspectFlags aspectFlags = VK_IMAGE_ASPECT_COLOR_BIT;
		};

		struct CopyBufferImageInfos
		{
			VkBuffer buffer = VK_NULL_HANDLE;

			Vec2ui extent;
			Format format = Format::RGBA_32;

			uint32 mipLevels = 1u;
			ImageType imageType = ImageType::Image2D;
		};


		void CreateImage(const Device& _device, const VkImageCreateInfo& _vkInfos);
		void CreateImageView(const Device& _device, const VkImageViewCreateInfo& _vkInfos);

		void Create(const Device& _device, const ImageBufferCreateInfos& _infos);
		void CreateFromImage(const Device& _device, const ImageBufferCreateInfos& _infos, VkImage& _image);

		void Destroy(const Device& _device);


		void TransitionImageLayout(CommandBuffer& _cmd, ResourceHolder& _resHold, const ImageBuffer::TransitionInfos& _infos);
		void CopyBufferToImage(CommandBuffer& _cmd, ResourceHolder& _resHold, const ImageBuffer::CopyBufferImageInfos& _infos);

		operator VkImage() const noexcept;
		operator VkImageView() const noexcept;
		operator VkDeviceMemory() const noexcept;
	};
}

#endif

#endif // GUARD
