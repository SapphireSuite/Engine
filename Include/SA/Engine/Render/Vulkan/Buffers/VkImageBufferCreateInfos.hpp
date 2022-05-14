// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_IMAGE_BUFFER_CREATE_INFOS_GUARD
#define SAPPHIRE_ENGINE_VK_IMAGE_BUFFER_CREATE_INFOS_GUARD

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Engine/Render/Base/Misc/Format.hpp>
#include <SA/Engine/Render/Base/Misc/ImageType.hpp>
#include <SA/Engine/Render/Base/Pass/SampleBits.hpp>

namespace SA::VK
{
	struct ImageBufferCreateInfos
	{
		uint32_t imageFlags = 0u;
		ImageType imageType = ImageType::Image2D;

		Format format = Format::RGBA_32;
		Vec2ui extent;

		uint32_t mipLevels = 1u;

		SampleBits sampling = SampleBits::Sample1Bit;
		VkImageTiling tiling = VK_IMAGE_TILING_OPTIMAL;

		uint32_t usage = 0u;

		VkImageAspectFlags aspectFlags = 0u;

		VkImageCreateInfo VkImageInfos() const noexcept;
		VkImageViewCreateInfo VkImageViewInfos(VkImage _image) const noexcept;
	};
}

#endif // GUARD
