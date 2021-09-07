// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_IMAGE_BUFFER_CREATE_INFOS_GUARD
#define SAPPHIRE_RENDER_VK_IMAGE_BUFFER_CREATE_INFOS_GUARD

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Render/Misc/Format.hpp>
#include <SA/Render/Misc/ImageType.hpp>
#include <SA/Render/Base/Pass/SampleBits.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	struct ImageBufferCreateInfos
	{
		uint32 imageFlags = 0u;
		ImageType imageType = ImageType::Image2D;

		Format format = Format::RGBA_32;
		Vec2ui extent;

		uint32 mipLevels = 1u;

		SampleBits sampling = SampleBits::Sample1Bit;
		VkImageTiling tiling = VK_IMAGE_TILING_OPTIMAL;

		uint32 usage = 0u;

		VkImageAspectFlags aspectFlags = 0u;

		VkImageCreateInfo VkImageInfos() const noexcept;
		VkImageViewCreateInfo VkImageViewInfos(VkImage _image) const noexcept;
	};
}

#endif

#endif // GUARD
