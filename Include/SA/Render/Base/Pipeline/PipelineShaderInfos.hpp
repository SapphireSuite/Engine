// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_PIPELINE_SHADER_INFOS_GUARD
#define SAPPHIRE_RENDER_PIPELINE_SHADER_INFOS_GUARD

#include <SA/Render/Base/Shader/AShader.hpp>
#include <SA/Render/Base/Shader/ShaderDescriptor.hpp>

#include <SA/Render/Base/Mesh/Vertex/VertexBindingLayout.hpp>

namespace Sa
{
	struct PipelineShaderStage
	{
		const AShader* shader = nullptr;

		ShaderStage stage = ShaderStage::Unknown;

		std::vector<SpecConstantDescriptor> userSpecConstants;
		std::vector<SpecConstantDescriptor> engineSpecConstants;
	};


	struct PipelineBindingDescriptor : public ShaderBindingDescriptor
	{
		Flags<ShaderStage> stageFlags;
	};

	struct PipelineBindingSetDescriptor
	{
		/// List of registered binding for set.
		std::vector<PipelineBindingDescriptor> bindings;
	};


	struct PipelineShaderInfos
	{
		VertexBindingLayout vertexBindingLayout;

		std::vector<PipelineShaderStage> stages;

		std::vector<PipelineBindingSetDescriptor> bindingSets;

		void AddShader(const AShader* _shader, const ShaderDescriptor& _descriptor);
	};
}

#endif // GUARD
