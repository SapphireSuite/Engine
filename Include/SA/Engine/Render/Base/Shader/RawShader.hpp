// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_RAW_SHADER_GUARD
#define SAPPHIRE_ENGINE_RAW_SHADER_GUARD

#include <cstdint>

#include <SA/Collections/SerializeBinary>

namespace SA
{
    struct RawShader
	{
		std::vector<uint32_t> data;

		void Clear();
	};


	namespace Ser
	{
		template <>
		bool ToBinary(const RawShader& _raw, std::string& _dst);

		template <>
		bool FromBinary(RawShader& _raw, const std::string& _src, size_t& _offset);
	}
}

#endif // GUARD
