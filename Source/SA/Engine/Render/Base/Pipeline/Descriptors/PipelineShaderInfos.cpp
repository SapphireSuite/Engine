// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Pipeline/Descriptors/PipelineShaderInfos.hpp>

#include <Render/Base/Shader/Descriptors/ShaderDescriptor.hpp>

namespace SA
{
	void PipelineShaderInfos::AddShader(const AShader* _shader, const ShaderDescriptor& _desc)
	{
		PipelineShaderStage& stage = stages.emplace_back();
		
		stage.shader = _shader;
		stage.stage = _desc.stage;
	}
}
