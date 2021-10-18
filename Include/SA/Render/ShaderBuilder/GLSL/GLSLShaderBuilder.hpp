// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_GLSL_SHADER_BUILDER_GUARD
#define SAPPHIRE_RENDER_GLSL_SHADER_BUILDER_GUARD

#include <SA/Render/ShaderBuilder/AShaderBuilderInterface.hpp>

#include <SA/Render/ShaderBuilder/GLSL/GLSLShaderCompiler.hpp>
#include <SA/Render/ShaderBuilder/GLSL/GLSLShaderReflector.hpp>

namespace Sa::GLSL
{
	class ShaderBuilder : public AShaderBuilderInterface
	{
		ShaderCompiler mCompiler;
		ShaderReflector mReflector;

	public:
		bool Build(const std::string& _path, RawShader& _raw, ShaderDescriptor& _desc) const override final;
	};
}

#endif // GUARD
