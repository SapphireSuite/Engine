// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Misc/Format.hpp>

#include <SA/Collections/Debug>

namespace SA
{
	Format::Format(FormatType _type, Flags<FormatFlags> _flags) noexcept :
		type{ _type },
		flags{ _flags }
	{
	}


	bool Format::IsColorFormat() const noexcept
	{
		return static_cast<uint8_t>(type) >= static_cast<uint8_t>(FormatType::R_8) &&
			static_cast<uint8_t>(type) <= static_cast<uint8_t>(FormatType::BGRA_32);
	}
	
	bool Format::IsPresentFormat() const noexcept
	{
		return flags.IsSet(FormatFlags::sRGB);
	}
	
	bool Format::IsDepthFormat() const noexcept
	{
		return static_cast<uint8_t>(type) >= static_cast<uint8_t>(FormatType::Stencil_8) &&
			static_cast<uint8_t>(type) <= static_cast<uint8_t>(FormatType::DepthStencil_32);
	}


	uint32_t API_GetChannelNum(Format _format)
	{
		switch (_format.type)
		{
			case FormatType::R_8:
			case FormatType::Stencil_8:
				return 1u;
			case FormatType::RG_16:
			case FormatType::Depth_16:
				return 2u;
			case FormatType::RGB_32:
			case FormatType::BGR_32:
			case FormatType::RGBA_32:
			case FormatType::BGRA_32:
			case FormatType::Depth_32:
			case FormatType::DepthStencil_32:
				return 4u;
			case FormatType::RGBA_64:
				return 8;
			default:
				SA_LOG(L"Format [" << _format << L"]not supported yet!", Error, SA/Enigne/Render/Vulkan);
				return 4u;
		}
	}


#if SA_VULKAN

	namespace VK
	{
		VkFormat SelectVkFormat(Flags<FormatFlags> _flags, VkFormat _uNormFormat)
		{
			uint32_t offset = 0u;

			if (_flags.IsSet(FormatFlags::Signed))
				offset += 1;

			if(_flags.IsSet(FormatFlags::sRGB) || _flags.IsSet(FormatFlags::Float))
				offset += 6;
			else if(_flags.IsSet(FormatFlags::Int))
				offset += 4;
			else if(!_flags.IsSet(FormatFlags::Norm))
				offset += 2;

			return (VkFormat)(_uNormFormat + offset);
		}

		VkFormat API_GetFormat(Format _format)
		{
			switch (_format.type)
			{
				// RGB.
				case FormatType::R_8:
					return SelectVkFormat(_format.flags, VK_FORMAT_R8_UNORM);
				case FormatType::RG_16:
					return SelectVkFormat(_format.flags, VK_FORMAT_R8G8_UNORM);
				case FormatType::RGB_32:
					return SelectVkFormat(_format.flags, VK_FORMAT_A2R10G10B10_UNORM_PACK32);
				case FormatType::BGR_32:
					return SelectVkFormat(_format.flags, VK_FORMAT_A2B10G10R10_UNORM_PACK32);
				case FormatType::RGBA_32:
					return SelectVkFormat(_format.flags, VK_FORMAT_R8G8B8A8_UNORM);
				case FormatType::BGRA_32:
					return SelectVkFormat(_format.flags, VK_FORMAT_B8G8R8A8_UNORM);
				case FormatType::RGBA_64:
					return SelectVkFormat(_format.flags, VK_FORMAT_R16G16B16A16_UNORM);

				// Depth
				case FormatType::Stencil_8:
					return VK_FORMAT_S8_UINT;
				case FormatType::Depth_16:
					return VK_FORMAT_D16_UNORM;
				case FormatType::Depth_32:
					return VK_FORMAT_D32_SFLOAT;
				case FormatType::DepthStencil_32:
					return VK_FORMAT_D24_UNORM_S8_UINT;

				default:
					SA_LOG(L"Format [" << _format << L"]not supported yet!", Error, SA/Engine/Render/Vulkan);
					return VK_FORMAT_R8G8B8A8_UNORM;
			}
		}


		bool IsInFormatRange(VkFormat _currFormat, VkFormat _minFormat, VkFormat _maxFormat)
		{
			return _currFormat >= _minFormat && _currFormat <= _maxFormat;
		}

		Flags<FormatFlags> SelectFormatFlags(VkFormat _currFormat, VkFormat _uNormFormat)
		{
			Flags<FormatFlags> flags;
			uint32_t offset = _currFormat - _uNormFormat;

			if (offset % 2 != 0)
			{
				flags.Add(FormatFlags::Signed);
				offset -= 1;
			}

			if(offset == 6)
				flags.Add(FormatFlags::Float).Add(FormatFlags::sRGB);
			else if(offset == 4)
				flags.Add(FormatFlags::Int);
			else if(offset == 2)
				flags.Add(FormatFlags::Norm);

			return flags;
		}


		Format API_FromFormat(VkFormat _vkFormat)
		{
			Format format;

			// RGB.

			if(IsInFormatRange(_vkFormat, VK_FORMAT_R8_UNORM, VK_FORMAT_R8_SRGB))
			{
				format.type = FormatType::R_8;
				format.flags = SelectFormatFlags(_vkFormat, VK_FORMAT_R8_UNORM);
			}
			else if(IsInFormatRange(_vkFormat, VK_FORMAT_R8G8_UNORM, VK_FORMAT_R8G8_SRGB))
			{
				format.type = FormatType::RG_16;
				format.flags = SelectFormatFlags(_vkFormat, VK_FORMAT_R8G8_UNORM);
			}
			else if(IsInFormatRange(_vkFormat, VK_FORMAT_A2R10G10B10_UNORM_PACK32, VK_FORMAT_A2R10G10B10_SINT_PACK32))
			{
				format.type = FormatType::RGB_32;
				format.flags = SelectFormatFlags(_vkFormat, VK_FORMAT_A2R10G10B10_UNORM_PACK32);
			}
			else if(IsInFormatRange(_vkFormat, VK_FORMAT_A2B10G10R10_UNORM_PACK32, VK_FORMAT_A2B10G10R10_SINT_PACK32))
			{
				format.type = FormatType::BGR_32;
				format.flags = SelectFormatFlags(_vkFormat, VK_FORMAT_A2B10G10R10_UNORM_PACK32);
			}
			else if(IsInFormatRange(_vkFormat, VK_FORMAT_R8G8B8A8_UNORM, VK_FORMAT_R8G8B8A8_SRGB))
			{
				format.type = FormatType::RGBA_32;
				format.flags = SelectFormatFlags(_vkFormat, VK_FORMAT_R8G8B8A8_UNORM);
			}
			else if(IsInFormatRange(_vkFormat, VK_FORMAT_B8G8R8A8_UNORM, VK_FORMAT_B8G8R8A8_SRGB))
			{
				format.type = FormatType::BGRA_32;
				format.flags = SelectFormatFlags(_vkFormat, VK_FORMAT_B8G8R8A8_UNORM);
			}
			else if(IsInFormatRange(_vkFormat, VK_FORMAT_R16G16B16A16_UNORM, VK_FORMAT_R16G16B16A16_SFLOAT))
			{
				format.type = FormatType::RGBA_64;
				format.flags = SelectFormatFlags(_vkFormat, VK_FORMAT_R16G16B16A16_UNORM);
			}
			
			// Depth
			else if(_vkFormat == VK_FORMAT_S8_UINT)
				format.type = FormatType::Stencil_8;
			else if(_vkFormat == VK_FORMAT_D16_UNORM)
				format.type = FormatType::Depth_16;
			else if(_vkFormat == VK_FORMAT_D32_SFLOAT)
				format.type = FormatType::Depth_32;
			else if(_vkFormat == VK_FORMAT_D24_UNORM_S8_UINT)
				format.type = FormatType::DepthStencil_32;

			// Default
			else
			{
				SA_LOG("Format [" << _vkFormat << L"] not supported yet!", Error, SA/Engine/Render/Vulkan);
			}

			return format;
		}
	}

#endif
}
