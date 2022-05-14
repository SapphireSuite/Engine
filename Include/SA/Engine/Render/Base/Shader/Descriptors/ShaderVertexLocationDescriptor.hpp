// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_SHADER_VERTEX_LOCATION_DESCRIPTOR_GUARD
#define SAPPHIRE_ENGINE_SHADER_VERTEX_LOCATION_DESCRIPTOR_GUARD

#include <cstdint>

#include <string>

namespace SA
{
	struct ShaderVertexLocationDescriptor
	{
		std::string name;

		uint32_t location = 0u;
		uint32_t size = 0u;

		bool operator<(const ShaderVertexLocationDescriptor& _rhs) const noexcept;
	};
}

#endif // GUARD
