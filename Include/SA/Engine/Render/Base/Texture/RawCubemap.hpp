// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_RAW_CUBEMAP_GUARD
#define SAPPHIRE_ENGINE_RAW_CUBEMAP_GUARD

#include <SA/Engine/Render/Base/Texture/RawTexture.hpp>

namespace SA
{
	struct RawCubemap : public RawTexture
	{
		std::vector<char> irradiancemapData;


		// Maximum rough level used for IBL. Generate as much mipmaps.
		static const uint32_t maxRoughLevel;


		// Compute original map size in format unit.
		uint64_t GetMapSize() const noexcept;

		// Compute total map size (including mipmaps) in format unit.
		uint64_t GetTotalMapSize() const noexcept;


		void Clear() override final;
	};


	namespace Ser
	{
		template <>
		bool ToBinary(const RawCubemap& _raw, std::string& _dst);

		template <>
		bool FromBinary(RawCubemap& _raw, const std::string& _src, size_t& _offset);
	}
}

#endif // GUARD
