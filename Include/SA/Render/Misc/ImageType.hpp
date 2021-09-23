// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_IMAGE_TYPE_GUARD
#define SAPPHIRE_RENDER_IMAGE_TYPE_GUARD

#include <SA/Core/Types/Int.hpp>

#include <SA/Core/Support/API/Vulkan.hpp>

namespace Sa
{
	enum class ImageType : uint8
	{
		/// Default 2D image.
		Image2D,

		Image3D,

		/// Cubemap.
		Cube,
	};

#if SA_VULKAN

	namespace Vk
	{
		VkImageType API_GetImageType(ImageType _type);

		VkImageViewType API_GetImageViewType(ImageType _type);

		uint32 API_GetLayerNum(ImageType _type);
	}

#endif
}

#endif // GUARD
