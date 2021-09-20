// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_SDK_SHADER_COMPILER_GUARD
#define SAPPHIRE_SDK_SHADER_COMPILER_GUARD

#include <shaderc/shaderc.hpp>

#include <SA/Core/Types/Int.hpp>

namespace Sa
{
	class ShaderCompiler
	{
		shaderc::Compiler mCompiler;

		std::string AssembleShader(const std::string& _path);

	public:
		bool Compile(const std::string& _path, std::vector<uint32>& _outCode);
	};
}

#endif // GUARD
