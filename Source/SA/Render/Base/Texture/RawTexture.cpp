// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Texture/RawTexture.hpp>

#include <Render/Base/Texture/Mipmap.hpp>

namespace Sa
{
	uint64 RawTexture::GetMainSize() const noexcept
	{
		return extent.x * extent.y * API_GetChannelNum(format);
	}

	// Compute total image size (including mipmaps) in format unit.
	uint64 RawTexture::GetTotalSize() const noexcept
	{
		return Mipmap::ComputeTotalSize(extent, mipLevels) * API_GetChannelNum(format);
	}
}
