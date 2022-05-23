// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_RAW_TEXTURE_GUARD
#define SAPPHIRE_ENGINE_RAW_TEXTURE_GUARD

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Engine/Render/Base/Misc/Format.hpp>

namespace SA
{
	struct RawTexture
	{
		Vec2ui extent;

		uint32_t mipLevels = 1u;

		Format format;

		std::vector<char> data;


		// Compute original image size in format unit.
		uint64_t GetMainSize() const noexcept;

		// Compute total image size (including mipmaps) in format unit.
		uint64_t GetTotalSize() const noexcept;


		virtual void Reset();
	};
}

#endif // GUARD
