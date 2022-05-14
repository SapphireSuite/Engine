// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_MIPMAP_GUARD
#define SAPPHIRE_ENGINE_MIPMAP_GUARD

#include <SA/Maths/Space/Vector2.hpp>

namespace SA
{
	class Mipmap
	{
	public:
		~Mipmap() = delete;

		static uint32_t ComputeLevels(const Vec2ui& _extent, uint32_t _minLevel = 0u) noexcept;
		static uint64_t ComputeTotalSize(Vec2ui _extent, uint32_t _mipmapLevels = 0u, Vec2ui* extents = nullptr) noexcept;
	};
}

#endif // GUARD
