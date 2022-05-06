// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_GLSL_SHADER_COMPILER_GUARD
#define SAPPHIRE_ENGINE_GLSL_SHADER_COMPILER_GUARD

#include <shaderc/shaderc.hpp>

namespace Sa
{
	struct RawShader;
	struct ShaderDescriptor;

	namespace GLSL
	{
		class ShaderCompiler
		{
			shaderc::Compiler mHandle;

			std::string AssembleShader(const std::string& _path) const;

		public:
			bool Compile(const std::string& _path, RawShader& _raw, ShaderDescriptor& _desc) const;
		};
	}
}

#endif // GUARD
