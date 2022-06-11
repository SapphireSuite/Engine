// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_GLSL_SHADER_BUILDER_GUARD
#define SAPPHIRE_ENGINE_GLSL_SHADER_BUILDER_GUARD

#include <SA/Engine/SDK/ShaderBuilder/AShaderBuilder.hpp>

#include <SA/Engine/SDK/ShaderBuilder/GLSL/GLSLShaderCompiler.hpp>
#include <SA/Engine/SDK/ShaderBuilder/GLSL/GLSLShaderReflector.hpp>

namespace SA::SDK::GLSL
{
	class ShaderBuilder : public AShaderBuilder
	{
		ShaderCompiler mCompiler;
		ShaderReflector mReflector;

	public:
		bool Build(const std::string& _path, RawShader& _raw, ShaderDescriptor& _desc) const override final;
	};
}

#endif // GUARD
