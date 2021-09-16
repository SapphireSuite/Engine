// Copyright 2020 Sapphire development team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_SDK_STB_IMAGE_GUARD
#define SAPPHIRE_SDK_STB_IMAGE_GUARD

#include <SA/Maths/Space/Vector2.hpp>

namespace Sa
{
	struct RawTexture;

	class StbImage
	{
		static bool GenerateMipMaps(const Vec2ui& _extent, uint32 _mipLevels, std::vector<char>& _data, uint32 _channelNum, uint32 _layerNum);

	public:
		static const uint32 bitSize;
		
		~StbImage() = delete;

		static bool Import(const std::string& _resourcePath, RawTexture& _result);
	};
}

#endif // GUARD
