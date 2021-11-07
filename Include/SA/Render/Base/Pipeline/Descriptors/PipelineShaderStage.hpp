// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_PIPELINE_SHADER_STAGE_GUARD
#define SAPPHIRE_RENDER_PIPELINE_SHADER_STAGE_GUARD

#include <SA/Render/Base/Shader/AShader.hpp>
#include <SA/Render/Base/Shader/Descriptors/ShaderStage.hpp>

namespace Sa
{
	struct PipelineShaderStage
	{
		const AShader* shader = nullptr;

		ShaderStage stage = ShaderStage::Unknown;
	};
}

#endif // GUARD
