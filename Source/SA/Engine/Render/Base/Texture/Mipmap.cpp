// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Texture/Mipmap.hpp>

namespace SA
{
	uint32_t Mipmap::ComputeLevels(const Vec2ui& _extent, uint32_t _minLevel) noexcept
	{
		// Source https://vulkan-tutorial.com/Generating_Mipmaps.

		return static_cast<uint32_t>(std::floor(std::log2(std::max(_extent.x, _extent.y)))) + 1 - _minLevel;
	}

	uint64_t Mipmap::ComputeTotalSize(Vec2ui _extent, uint32_t _mipmapLevels, Vec2ui* _extents) noexcept
	{
		if (_mipmapLevels == 0u)
			_mipmapLevels = ComputeLevels(_extent);


		uint64_t totalSize = 0u;

		for (uint32_t i = 0u; i < _mipmapLevels; ++i)
		{
			if (_extents)
				_extents[i] = _extent;

			totalSize += _extent.x * _extent.y;

			if (_extent.x > 1)
				_extent.x >>= 1;

			if (_extent.y > 1)
				_extent.y >>= 1;
		}

		return totalSize;
	}
}
