// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Texture/RawCubemap.hpp>

namespace SA
{
	const uint32_t RawCubemap::maxRoughLevel = 5u;


	uint64_t RawCubemap::GetMapSize() const noexcept
	{
		return GetMainSize() * 6u;
	}

	uint64_t RawCubemap::GetTotalMapSize() const noexcept
	{
		return GetTotalSize() * 6u;
	}


	void RawCubemap::Clear()
	{
		RawTexture::Clear();

		irradiancemapData.clear();
	}


	namespace Ser
	{
		template <>
		bool ToBinary(const RawCubemap& _raw, std::string& _dst)
		{
			ToBinary<RawTexture>(_raw, _dst);
			ToBinary(_raw.irradiancemapData, _dst);

			return true;
		}

		template <>
		bool FromBinary(RawCubemap& _raw, const std::string& _src, size_t& _offset)
		{
			FromBinary<RawTexture>(_raw, _src, _offset);
			FromBinary(_raw.irradiancemapData, _src, _offset);

			return true;
		}
	}
}
