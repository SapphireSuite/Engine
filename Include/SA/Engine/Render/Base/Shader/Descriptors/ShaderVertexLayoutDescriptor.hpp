// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_SHADER_VERTEX_LAYOUT_DESCRIPTOR_GUARD
#define SAPPHIRE_ENGINE_SHADER_VERTEX_LAYOUT_DESCRIPTOR_GUARD

#include <SA/Engine/Render/Base/Shader/Descriptors/ShaderVertexLocationDescriptor.hpp>

namespace SA
{
	struct ShaderVertexLayoutDescriptor
	{
		std::vector<ShaderVertexLocationDescriptor> locations;

		void Clear();
	};


	namespace Ser
	{
		template <>
		bool ToBinary(const ShaderVertexLayoutDescriptor& _desc, std::string& _dst);

		template <>
		bool FromBinary(ShaderVertexLayoutDescriptor& _desc, const std::string& _src, size_t& _offset);
	}
}

#endif // GUARD
