// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Texture/RawTexture.hpp>

#include <Core/Serialize/Serializer.hpp>

#include <Render/Base/Texture/Mipmap.hpp>

namespace Sa
{
	uint64 RawTexture::GetMainSize() const noexcept
	{
		return extent.x * extent.y * API_GetChannelNum(format);
	}

	// Compute total image size (including mipmaps) in format unit.
	uint64 RawTexture::GetTotalSize() const noexcept
	{
		return Mipmap::ComputeTotalSize(extent, mipLevels) * API_GetChannelNum(format);
	}


	void RawTexture::Reset()
	{
		data.clear();
		
		mipLevels = 1u;
		extent = Vec2ui::Zero;
		format = Format::RGBA_32;
	}


	namespace Serialize
	{
		void ToBinary(const RawTexture& _obj, std::string& _str)
		{
			// Raw serialize until data.
			Intl::ToBinary(&_obj, offsetof(RawTexture, data), _str);

			ToBinary(_obj.data, _str);
		}

		void FromBinary(RawTexture& _obj, Reader& _read)
		{
			Intl::FromBinary(&_obj, offsetof(RawTexture, data), _read);

			FromBinary(_obj.data, _read);
		}
	}
}
