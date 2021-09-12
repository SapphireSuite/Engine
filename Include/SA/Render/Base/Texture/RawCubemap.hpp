// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RAW_CUBEMAP_GUARD
#define SAPPHIRE_RENDER_RAW_CUBEMAP_GUARD

#include <SA/Render/Base/Texture/RawTexture.hpp>

namespace Sa
{
	struct RawCubemap : public RawTexture
	{
		std::vector<char> irradiancemapData;


		// Maximum rough level used for IBL. Generate as much mipmaps.
		static const uint32 maxRoughLevel;


		// Compute original map size in format unit.
		uint64 GetMapSize() const noexcept;

		// Compute total map size (including mipmaps) in format unit.
		uint64 GetTotalMapSize() const noexcept;
	};
}

#endif // GUARD
