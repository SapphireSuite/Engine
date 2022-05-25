// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Texture/RawTexture.hpp>

#include <Render/Base/Texture/Mipmap.hpp>

namespace SA
{
	uint64_t RawTexture::GetMainSize() const noexcept
	{
		return extent.x * extent.y * API_GetChannelNum(format);
	}

	// Compute total image size (including mipmaps) in format unit.
	uint64_t RawTexture::GetTotalSize() const noexcept
	{
		return Mipmap::ComputeTotalSize(extent, mipLevels) * API_GetChannelNum(format);
	}


	void RawTexture::Clear()
	{
		data.clear();
		
		mipLevels = 1u;
		extent = Vec2ui::Zero;
		format = Format(FormatType::RGBA_32, FormatFlags::Norm);
	}


	namespace Ser
	{
		template <>
		bool ToBinary(const RawTexture& _raw, std::string& _dst)
		{
			ToBinary(_raw.extent, _dst);
			ToBinary(_raw.mipLevels, _dst);
			ToBinary(_raw.format, _dst);
			ToBinary(_raw.data, _dst);

			return true;
		}

		template <>
		bool FromBinary(RawTexture& _raw, const std::string& _src, size_t& _offset)
		{
			FromBinary(_raw.extent, _src, _offset);
			FromBinary(_raw.mipLevels, _src, _offset);
			FromBinary(_raw.format, _src, _offset);
			FromBinary(_raw.data, _src, _offset);

			return true;
		}
	}
}
