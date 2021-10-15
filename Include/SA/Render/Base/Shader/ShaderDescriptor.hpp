// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SHADER_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_SHADER_DESCRIPTOR_GUARD

#include <set>
#include <vector>

#include <SA/Render/Base/Shader/ShaderStage.hpp>
#include <SA/Render/Base/Shader/Bindings/ShaderBindingSetDescriptor.hpp>
#include <SA/Render/Base/Shader/SpecConstants/SpecConstantDescriptor.hpp>

#include <SA/Render/Base/Mesh/Vertex/VertexComp.hpp>

namespace Sa
{
	struct ShaderDescriptor
	{
		ShaderStage stage = ShaderStage::Unknown;

		/// Vertex layout (valid only if stage == Vertex).
		Flags<VertexComp> vertexLayout;

		ShaderBindingSetDescriptor userBindingSet;
		std::set<uint32> engineBindingSets;

		std::vector<SpecConstantDescriptor> userSpecConstants;
		std::vector<SpecConstantDescriptor> engineSpecConstants;


		SpecConstantDescriptor& EmplaceSpecConstants(uint32 _id);

		void Clear();
	};


	namespace Serialize
	{
		void ToBinary(const ShaderDescriptor& _obj, std::string& _str);
		void FromBinary(ShaderDescriptor& _obj, Reader& _read);
	}
}

#endif // GUARD
