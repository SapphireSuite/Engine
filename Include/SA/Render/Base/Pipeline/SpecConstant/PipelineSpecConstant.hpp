// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_PIPELINE_SPEC_CONSTANT_GUARD
#define SAPPHIRE_RENDER_PIPELINE_SPEC_CONSTANT_GUARD

#include <memory>

#include <SA/Render/Base/Shader/Descriptors/ShaderSpecConstantDescriptor.hpp>

#include <SA/Render/Base/Pipeline/SpecConstant/SpecConstant.hpp>

namespace Sa
{
	struct PipelineSpecConstant : public ShaderSpecConstantDescriptor
	{
		std::unique_ptr<SpecConstantBase> value;
	};
}

#endif // GUARD
