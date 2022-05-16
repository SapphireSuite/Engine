// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_PIPELINE_SHADER_STAGE_GUARD
#define SAPPHIRE_ENGINE_PIPELINE_SHADER_STAGE_GUARD

#include <SA/Engine/Render/Base/Shader/AShader.hpp>
#include <SA/Engine/Render/Base/Shader/Descriptors/ShaderStage.hpp>

namespace SA
{
	struct PipelineShaderStage
	{
		const AShader* shader = nullptr;

		ShaderStage stage = ShaderStage::Unknown;
	};
}

#endif // GUARD
