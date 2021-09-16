// Copyright 2020 Sapphire development team. All Rights Reserved.

#include <SDK/Wrappers/StbImage.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb_image_resize.h>

#include <Render/Base/Texture/RawTexture.hpp>
#include <Render/Base/Texture/Mipmap.hpp>

namespace Sa
{
	auto init = []()
	{
		stbi_set_flip_vertically_on_load(true);
	};

	const uint32 StbImage::bitSize = sizeof(stbi_uc);


	bool StbImage::Import(const std::string& _resourcePath, RawTexture& _result)
	{
		uint32 channelNum = 0u;
		Format importFormat = Format::RGBA_32;

		// Load texture.
		char* data = reinterpret_cast<char*>(stbi_load(_resourcePath.c_str(),
			reinterpret_cast<int32*>(&_result.extent.x),
			reinterpret_cast<int32*>(&_result.extent.y),
			reinterpret_cast<int32*>(&channelNum),
			API_GetChannelNum(importFormat)
		));

		if (!data)
		{
			SA_LOG("Failed to import {" << _resourcePath << L"} texture image!", Error, SA/SDK/Wrappers/STB);
			return false;
		}


		_result.format = importFormat;
		_result.data.assign(data, data + _result.GetMainSize());

		stbi_image_free(data);

		_result.mipLevels = Mipmap::ComputeLevels(_result.extent);
		
		return GenerateMipMaps(_result.extent, _result.mipLevels, _result.data, API_GetChannelNum(importFormat), 1u);
	}



	bool StbImage::GenerateMipMaps(const Vec2ui& _extent, uint32 _mipLevels, std::vector<char>& _data, uint32 _channelNum, uint32 _layerNum)
	{
		std::vector<Vec2ui> extents(_mipLevels);

		const uint64 totalSize = Mipmap::ComputeTotalSize(_extent, _mipLevels, extents.data()) * _channelNum * _layerNum * bitSize;

		_data.resize(totalSize);

		unsigned char* src = reinterpret_cast<unsigned char*>(_data.data());

		for (uint32 i = 1u; i < _mipLevels; ++i)
		{
			const uint64 srcLayerOffset = extents[i - 1].x * extents[i - 1].y * _channelNum * bitSize;
			const uint64 currLayerOffset = extents[i].x * extents[i].y * _channelNum * bitSize;
			unsigned char* dst = src + srcLayerOffset * _layerNum;

			for (uint32 j = 0; j < _layerNum; ++j)
			{
				bool res = stbir_resize_uint8(
					src,
					static_cast<int32>(extents[i - 1].x),
					static_cast<int32>(extents[i - 1].y),
					0,
					dst,
					static_cast<int32>(extents[i].x),
					static_cast<int32>(extents[i].y),
					0,
					_channelNum
				);

				if (!res)
				{
					SA_LOG(L"Mipmap creation failed!", Error, SA/SDK/Wrappers/STB);
					return false;
				}

				dst += currLayerOffset;
				src += srcLayerOffset;
			}
		}

		return true;
	}
}
