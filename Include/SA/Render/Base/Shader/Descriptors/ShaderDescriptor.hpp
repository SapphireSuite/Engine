// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SHADER_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_SHADER_DESCRIPTOR_GUARD

#include <set>
#include <vector>

#include <SA/Render/Base/Shader/Descriptors/ShaderStage.hpp>
#include <SA/Render/Base/Shader/Descriptors/ShaderBindingSetDescriptor.hpp>
#include <SA/Render/Base/Shader/Descriptors/ShaderPushConstantDescriptor.hpp>
#include <SA/Render/Base/Shader/Descriptors/ShaderSpecConstantDescriptor.hpp>

#include <SA/Render/Base/Mesh/Vertex/VertexComp.hpp>

namespace Sa
{
	struct ShaderDescriptor
	{
		ShaderStage stage = ShaderStage::Unknown;

		/// Vertex layout (valid only if stage == Vertex).
		Flags<VertexComp> vertexLayout;

		std::vector<ShaderBindingSetDescriptor> bindingSet;
		std::vector<ShaderPushConstantDescriptor> pushConstants;
		std::vector<ShaderSpecConstantDescriptor> specConstants;


		ShaderBindingDescriptor& EmplaceBinding(uint32 _set);

		void Clear();
	};


	namespace Serialize
	{
		void ToBinary(const ShaderDescriptor& _obj, std::string& _str);
		void FromBinary(ShaderDescriptor& _obj, Reader& _read);
	}
}

#endif // GUARD
