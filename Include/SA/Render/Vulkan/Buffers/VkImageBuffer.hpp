// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#ifndef SAPPHIRE_RENDER_VK_IMAGE_BUFFER_GUARD
#define SAPPHIRE_RENDER_VK_IMAGE_BUFFER_GUARD

#include <Render/Vulkan/Buffers/VkImageBufferCreateInfos.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	class Device;

	class ImageBuffer
	{
		VkImage mImage = VK_NULL_HANDLE;
		VkImageView mImageView = VK_NULL_HANDLE;
		VkDeviceMemory mImageMemory = VK_NULL_HANDLE;

	public:
		void CreateImage(const Device& _device, const VkImageCreateInfo& _vkInfos);
		void CreateImageView(const Device& _device, const VkImageViewCreateInfo& _vkInfos);

		void Create(const Device& _device, const ImageBufferCreateInfos& _infos);
		void CreateFromImage(const Device& _device, const ImageBufferCreateInfos& _infos, VkImage& _image);

		void Destroy(const Device& _device);


		operator VkImage() const noexcept;
		operator VkImageView() const noexcept;
		operator VkDeviceMemory() const noexcept;
	};
}

#endif

#endif // GUARD
