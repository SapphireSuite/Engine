// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_IMAGE_TYPE_GUARD
#define SAPPHIRE_ENGINE_IMAGE_TYPE_GUARD

#include <cstdint>

#include <SA/Support/API/Vulkan.hpp>

namespace Sa
{
	enum class ImageType : uint8_t
	{
		/// Default 2D image.
		Image2D,

		/// Default 3D image.
		Image3D,

		/// Cubemap.
		Cube,
	};

#if SA_VULKAN

	namespace Vk
	{
		VkImageType API_GetImageType(ImageType _type);

		VkImageViewType API_GetImageViewType(ImageType _type);

		uint32_t API_GetLayerNum(ImageType _type);
	}

#endif
}

#endif // GUARD
