// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_MIPMAP_GUARD
#define SAPPHIRE_RENDER_MIPMAP_GUARD

#include <SA/Maths/Space/Vector2.hpp>

namespace Sa
{
	class Mipmap
	{
	public:
		~Mipmap() = delete;

		static uint32 ComputeLevels(const Vec2ui& _extent, uint32 _minLevel = 0u) noexcept;
		static uint64 ComputeTotalSize(Vec2ui _extent, uint32 _mipmapLevels = 0u, Vec2ui* extents = nullptr) noexcept;
	};
}

#endif // GUARD
