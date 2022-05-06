// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_SHADER_VERTEX_LAYOUT_DESCRIPTOR_GUARD
#define SAPPHIRE_ENGINE_SHADER_VERTEX_LAYOUT_DESCRIPTOR_GUARD

#include <vector>

#include <SA/Engine/Render/Base/Shader/Descriptors/ShaderVertexLocationDescriptor.hpp>

namespace Sa
{
	struct ShaderVertexLayoutDescriptor
	{
		std::vector<ShaderVertexLocationDescriptor> locations;
	};
}

#endif // GUARD
