// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Texture/RawCubemap.hpp>

namespace Sa
{
	const uint32 RawCubemap::maxRoughLevel = 5u;

	uint64 RawCubemap::GetMapSize() const noexcept
	{
		return GetMainSize() * 6u;
	}

	uint64 RawCubemap::GetTotalMapSize() const noexcept
	{
		return GetTotalSize() * 6u;
	}
}
