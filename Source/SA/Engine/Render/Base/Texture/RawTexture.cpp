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


	void RawTexture::Reset()
	{
		data.clear();
		
		mipLevels = 1u;
		extent = Vec2ui::Zero;
		format = Format::RGBA_32;
	}
}
