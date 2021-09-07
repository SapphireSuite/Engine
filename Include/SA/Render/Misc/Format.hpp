// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_FORMAT_GUARD
#define SAPPHIRE_RENDER_FORMAT_GUARD

#include <SA/Core/Types/Int.hpp>

#include <SA/Core/Support/API/Vulkan.hpp>

namespace Sa
{
	enum class Format : uint8
	{
		// RGB formats.
		R_8,
		RG_16,

		RGB_32,
		BGR_32,

		RGBA_32,
		BGRA_32,

		RGBA_64,


		// sRGB formats.
		sR_8,
		sRG_16,

		sRGBA_32,
		sBGRA_32,


		// Depth formats.
		Stencil_8,
		Depth_16,
		Depth_32,
		DepthStencil_32,
	};

	bool IsColorFormat(Format _format) noexcept;
	bool IsPresentFormat(Format _format) noexcept;
	bool IsDepthFormat(Format _format) noexcept;

#if SA_VULKAN

	namespace Vk
	{
		VkFormat API_GetFormat(Format _format);
		Format API_FromFormat(VkFormat _format);

		uint32 API_GetChannelNum(Format _format);
	}
	
#endif
}

#endif // GUARD
