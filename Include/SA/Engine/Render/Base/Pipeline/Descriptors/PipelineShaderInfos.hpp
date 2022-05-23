// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_PIPELINE_SHADER_INFOS_GUARD
#define SAPPHIRE_ENGINE_PIPELINE_SHADER_INFOS_GUARD

#include <vector>

#include <SA/Engine/Render/Base/Pipeline/Descriptors/PipelineShaderStage.hpp>
#include <SA/Engine/Render/Base/Pipeline/Descriptors/PipelineVertexLayoutDescriptor.hpp>

namespace SA
{
	struct ShaderDescriptor;

	struct PipelineShaderInfos
	{
		std::vector<PipelineShaderStage> stages;

		PipelineVertexLayoutDescriptor vertexLayoutDesc;


		void AddShader(const AShader* _shader, const ShaderDescriptor& _desc);

	private:
		void AddShaderStage(const AShader* _shader, const ShaderDescriptor& _desc);

		void AddVertexLayout(const ShaderVertexLayoutDescriptor& _vertLayoutDesc);
	};
}

#endif // GUARD
