// Copyright 2022 Sapphire development team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_STB_IMAGE_GUARD
#define SAPPHIRE_ENGINE_STB_IMAGE_GUARD

#include <SA/Maths/Space/Vector2.hpp>

namespace SA
{
	struct RawTexture;

	class StbImage
	{
		static bool GenerateMipMaps(const Vec2ui& _extent,
			uint32_t _mipLevels, std::vector<char>& _data,
			uint32_t _channelNum,
			uint32_t _layerNum);

	public:
		static const uint32_t bitSize;
		
		~StbImage() = delete;

		static bool Import(const std::string& _resourcePath, RawTexture& _result);
	};
}

#endif // GUARD
