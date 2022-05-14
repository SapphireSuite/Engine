// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Texture/RawCubemap.hpp>

namespace SA
{
	const uint32_t RawCubemap::maxRoughLevel = 5u;


	uint64_t RawCubemap::GetMapSize() const noexcept
	{
		return GetMainSize() * 6u;
	}

	uint64_t RawCubemap::GetTotalMapSize() const noexcept
	{
		return GetTotalSize() * 6u;
	}


	void RawCubemap::Reset()
	{
		RawTexture::Reset();

		irradiancemapData.clear();
	}
}
