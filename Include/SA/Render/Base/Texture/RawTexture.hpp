// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RAW_TEXTURE_GUARD
#define SAPPHIRE_RENDER_RAW_TEXTURE_GUARD

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Render/Misc/Format.hpp>

namespace Sa
{
	struct RawTexture
	{
		Vec2ui extent;

		std::vector<char> data;

		uint32 mipLevels = 1u;

		Format format = Format::RGBA_32;


		// Compute original image size in format unit.
		uint64 GetMainSize() const noexcept;

		// Compute total image size (including mipmaps) in format unit.
		uint64 GetTotalSize() const noexcept;
	};
}

#endif // GUARD
