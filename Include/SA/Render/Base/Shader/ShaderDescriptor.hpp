// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SHADER_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_SHADER_DESCRIPTOR_GUARD

#include <vector>

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

		std::vector<ShaderBindingDescriptor> userBindings;
		std::vector<ShaderBindingDescriptor> engineBindings;

		std::vector<SpecConstantDescriptor> userSpecConstants;
		std::vector<SpecConstantDescriptor> engineSpecConstants;


		ShaderBindingDescriptor& EmplaceBinding(uint32 _set);
		SpecConstantDescriptor& EmplaceSpecConstants(uint32 _id);

		void Reset();
	};


	namespace Serialize
	{
		void ToBinary(const ShaderDescriptor& _obj, std::string& _str);
		void FromBinary(ShaderDescriptor& _obj, Reader& _read);
	}
}

#endif // GUARD
