// Copyright 2022 Sapphire development team. All Rights Reserved.

#include <SDK/Wrappers/StbImage.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb_image_resize.h>

#include <Render/Base/Texture/RawTexture.hpp>
#include <Render/Base/Texture/Mipmap.hpp>

namespace SA
{
	// auto init = []()
	// {
	// 	stbi_set_flip_vertically_on_load(true);
	// 	return true;
	// }();

	const uint32_t StbImage::bitSize = sizeof(stbi_uc);


	bool StbImage::Import(const std::string& _resourcePath, RawTexture& _result)
	{
		uint32_t channelNum = 0u;
		Format importFormat(FormatType::RGBA_32);

		// Load texture.
		char* data = reinterpret_cast<char*>(stbi_load(_resourcePath.c_str(),
			reinterpret_cast<int32_t*>(&_result.extent.x),
			reinterpret_cast<int32_t*>(&_result.extent.y),
			reinterpret_cast<int32_t*>(&channelNum),
			API_GetChannelNum(importFormat)
		));

		if (!data)
		{
			SA_LOG("Failed to import {" << _resourcePath << L"} texture image!", Error, SA/Engine/SDK/Wrappers/STB);
			return false;
		}


		_result.format = importFormat;
		_result.data.assign(data, data + _result.GetMainSize());

		stbi_image_free(data);

		_result.mipLevels = Mipmap::ComputeLevels(_result.extent);
		
		return GenerateMipMaps(_result.extent, _result.mipLevels, _result.data, API_GetChannelNum(importFormat), 1u);
	}



	bool StbImage::GenerateMipMaps(const Vec2ui& _extent,
		uint32_t _mipLevels,
		std::vector<char>& _data,
		uint32_t _channelNum,
		uint32_t _layerNum)
	{
		std::vector<Vec2ui> extents(_mipLevels);

		const uint64_t totalSize = Mipmap::ComputeTotalSize(_extent, _mipLevels, extents.data()) * _channelNum * _layerNum * bitSize;

		_data.resize(totalSize);

		unsigned char* src = reinterpret_cast<unsigned char*>(_data.data());

		for (uint32_t i = 1u; i < _mipLevels; ++i)
		{
			const uint64_t srcLayerOffset = extents[i - 1].x * extents[i - 1].y * _channelNum * bitSize;
			const uint64_t currLayerOffset = extents[i].x * extents[i].y * _channelNum * bitSize;
			unsigned char* dst = src + srcLayerOffset * _layerNum;

			for (uint32_t j = 0; j < _layerNum; ++j)
			{
				bool res = stbir_resize_uint8(
					src,
					static_cast<int32_t>(extents[i - 1].x),
					static_cast<int32_t>(extents[i - 1].y),
					0,
					dst,
					static_cast<int32_t>(extents[i].x),
					static_cast<int32_t>(extents[i].y),
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
