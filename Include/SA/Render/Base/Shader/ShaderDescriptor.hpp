// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SHADER_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_SHADER_DESCRIPTOR_GUARD

#include <vector>
#include <unordered_map>

#include <SA/Render/Base/Shader/ShaderStage.hpp>
#include <SA/Render/Base/Shader/Bindings/ShaderBindingDescriptor.hpp>
#include <SA/Render/Base/Shader/SpecConstants/SpecConstantDescriptor.hpp>

#include <SA/Render/Base/Mesh/Vertex/VertexComp.hpp>

namespace Sa
{
	struct ShaderDescriptor
	{
		ShaderStage stage = ShaderStage::Unknown;

		/// Vertex layout (valid only if stage == Vertex).
		Flags<VertexComp> vertexLayout;

		std::unordered_map<std::string, ShaderBindingDescriptor> bindings;
		std::unordered_map<std::string, SpecConstantDescriptor> specConstants;
	};
}

#endif // GUARD
