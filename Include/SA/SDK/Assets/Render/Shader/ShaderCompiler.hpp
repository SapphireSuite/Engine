// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_SDK_SHADER_COMPILER_GUARD
#define SAPPHIRE_SDK_SHADER_COMPILER_GUARD

#include <shaderc/shaderc.hpp>

namespace Sa
{
	struct RawShader;

	class ShaderCompiler
	{
		shaderc::Compiler mHandle;

		std::string AssembleShader(const std::string& _path);

	public:
		bool Compile(const std::string& _path, RawShader& _raw);
	};
}

#endif // GUARD
