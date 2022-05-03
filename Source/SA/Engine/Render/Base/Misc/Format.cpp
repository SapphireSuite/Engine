// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Misc/Format.hpp>

#include <SA/Collections/Debug>

namespace Sa
{
	bool IsColorFormat(Format _format) noexcept
	{
		return static_cast<uint8_t>(_format) >= static_cast<uint8_t>(Format::R_8) &&
			static_cast<uint8_t>(_format) <= static_cast<uint8_t>(Format::BGRA_32);
	}
	
	bool IsPresentFormat(Format _format) noexcept
	{
		return static_cast<uint8_t>(_format) >= static_cast<uint8_t>(Format::sR_8) &&
			static_cast<uint8_t>(_format) <= static_cast<uint8_t>(Format::sBGRA_32);
	}
	
	bool IsDepthFormat(Format _format) noexcept
	{
		return static_cast<uint8_t>(_format) >= static_cast<uint8_t>(Format::Stencil_8) &&
			static_cast<uint8_t>(_format) <= static_cast<uint8_t>(Format::DepthStencil_32);
	}


	uint32_t API_GetChannelNum(Format _format)
	{
		switch (_format)
		{
			case Format::R_8:
			case Format::sR_8:
			case Format::Stencil_8:
				return 1u;
			case Format::RG_16:
			case Format::sRG_16:
			case Format::Depth_16:
				return 2u;
			case Format::RGB_32:
			case Format::BGR_32:
			case Format::RGBA_32:
			case Format::BGRA_32:
			case Format::sRGBA_32:
			case Format::sBGRA_32:
			case Format::Depth_32:
			case Format::DepthStencil_32:
				return 4u;
			case Format::RGBA_64:
				return 8;
			default:
				SA_LOG(L"Format [" << _format << L"]not supported yet!", Error, SA/Enigne/Render/Vulkan);
				return 4u;
		}
	}


#if SA_VULKAN

	namespace Vk
	{
		VkFormat API_GetFormat(Format _format)
		{
			switch (_format)
			{
				// RGB.
				case Format::R_8:
					return VK_FORMAT_R8_UNORM;
				case Format::RG_16:
					return VK_FORMAT_R8G8_UNORM;
				case Format::RGB_32:
					return VK_FORMAT_A2R10G10B10_UNORM_PACK32;
				case Format::BGR_32:
					return VK_FORMAT_A2B10G10R10_UNORM_PACK32;
				case Format::RGBA_32:
					return VK_FORMAT_R8G8B8A8_UNORM;
				case Format::BGRA_32:
					return VK_FORMAT_B8G8R8A8_UNORM;
				case Format::RGBA_64:
					return VK_FORMAT_R16G16B16A16_SFLOAT;

				// sRGB.
				case Format::sR_8:
					return VK_FORMAT_R8_SRGB;
				case Format::sRG_16:
					return VK_FORMAT_R8G8_SRGB;
				case Format::sRGBA_32:
					return VK_FORMAT_R8G8B8A8_SRGB;
				case Format::sBGRA_32:
					return VK_FORMAT_B8G8R8A8_SRGB;

				// Depth
				case Format::Stencil_8:
					return VK_FORMAT_S8_UINT;
				case Format::Depth_16:
					return VK_FORMAT_D16_UNORM;
				case Format::Depth_32:
					return VK_FORMAT_D32_SFLOAT;
				case Format::DepthStencil_32:
					return VK_FORMAT_D24_UNORM_S8_UINT;

				default:
					SA_LOG(L"Format [" << _format << L"]not supported yet!", Error, SA/Engine/Render/Vulkan);
					return VK_FORMAT_R8G8B8A8_UNORM;
			}
		}

		Format API_FromFormat(VkFormat _format)
		{
			switch (_format)
			{
				// RGB.
				case VK_FORMAT_R8_UNORM:
					return Format::R_8;
				case VK_FORMAT_R8G8_UNORM:
					return Format::RG_16;
				case VK_FORMAT_A2R10G10B10_UNORM_PACK32:
					return Format::RGB_32;
				case VK_FORMAT_A2B10G10R10_UNORM_PACK32:
					return Format::BGR_32;
				case VK_FORMAT_R8G8B8A8_UNORM:
					return Format::RGBA_32;
				case VK_FORMAT_B8G8R8A8_UNORM:
					return Format::BGRA_32;
				case VK_FORMAT_R16G16B16A16_SFLOAT:
					return Format::RGBA_64;

				// sRGB.
				case VK_FORMAT_R8_SRGB:
					return Format::sR_8;
				case VK_FORMAT_R8G8_SRGB:
					return Format::sRG_16;
				case VK_FORMAT_R8G8B8A8_SRGB:
					return Format::sRGBA_32;
				case VK_FORMAT_B8G8R8A8_SRGB:
					return Format::sBGRA_32;

				// Depth
				case VK_FORMAT_S8_UINT:
					return Format::Stencil_8;
				case VK_FORMAT_D16_UNORM:
					return Format::Depth_16;
				case VK_FORMAT_D32_SFLOAT:
					return Format::Depth_32;
				case VK_FORMAT_D24_UNORM_S8_UINT:
					return Format::DepthStencil_32;

				default:
					SA_LOG("Format [" << _format << L"]not supported yet!", Error, SA/Engine/Render/Vulkan);
					return Format::RGBA_32;
			}
		}
	}

#endif
}
