// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_PIPELINE_SHADER_INFOS_GUARD
#define SAPPHIRE_ENGINE_PIPELINE_SHADER_INFOS_GUARD

#include <vector>

#include <SA/Engine/Render/Base/Pipeline/Descriptors/PipelineShaderStage.hpp>

namespace SA
{
	struct ShaderDescriptor;

	struct PipelineShaderInfos
	{
		// VertexBindingLayout vertexBindingLayout;

		std::vector<PipelineShaderStage> stages;

		void AddShader(const AShader* _shader, const ShaderDescriptor& _desc);
	};
}

#endif // GUARD
