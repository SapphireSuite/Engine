// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_RAW_SHADER_GUARD
#define SAPPHIRE_ENGINE_RAW_SHADER_GUARD

#include <cstdint>
#include <vector>

namespace Sa
{
    struct RawShader
	{
		std::vector<uint32_t> data;

		void Clear();
	};
}

#endif // GUARD
