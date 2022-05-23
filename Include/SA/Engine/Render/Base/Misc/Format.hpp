// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_FORMAT_GUARD
#define SAPPHIRE_ENGINE_FORMAT_GUARD

#include <SA/Support/API/Vulkan.hpp>

#include <SA/Flags/Flags.hpp>

namespace SA
{
	enum class FormatType : uint8_t
	{
		// RGB formats.
		R_8,
		RG_16,

		RGB_32,
		BGR_32,

		RGBA_32,
		BGRA_32,

		RGBA_64,


		// Depth formats.
		Stencil_8,
		Depth_16,
		Depth_32,
		DepthStencil_32,
	};


	enum class FormatFlags : uint8_t
	{
		/// Signed / Unsigned flag bit.
		Signed = 1 << 0,

		/// Normalized / Scaled flag bit.
		Norm = 1 << 1,

		/// Integer format flag bit.
		Int = 1 << 2,

		/// Float format flag bit.
		Float = 1 << 3,

		/// sRGB format flag bit.
		sRGB = 1 << 4,
	};

	SA_DEFINE_ENUM_FLAGS(FormatFlags)


	struct Format
	{
		FormatType type = FormatType::RGBA_32;

		Flags<FormatFlags> flags = FormatFlags::Norm;


		Format(FormatType _type = FormatType::RGBA_32, Flags<FormatFlags> _flags = FormatFlags::Norm) noexcept;

		bool IsColorFormat() const noexcept;
		bool IsPresentFormat() const noexcept;
		bool IsDepthFormat() const noexcept;
	};


	uint32_t API_GetChannelNum(Format _format);

#if SA_VULKAN

	namespace VK
	{
		VkFormat API_GetFormat(Format _format);
		Format API_FromFormat(VkFormat _format);
	}
	
#endif
}

#endif // GUARD
