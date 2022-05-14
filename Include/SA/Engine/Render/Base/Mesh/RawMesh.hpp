// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_RAW_MESH_GUARD
#define SAPPHIRE_ENGINE_RAW_MESH_GUARD

#include <cstdint>
#include <vector>

namespace Sa
{
	struct RawMesh
	{
		std::vector<char> vertices;
		std::vector<uint32_t> indices;

		void Reset();
	};
}

#endif // GUARD
