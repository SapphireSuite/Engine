// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SDK/ShaderBuilder/GLSL/GLSLShaderBuilder.hpp>

namespace SA::SDK::GLSL
{
	bool ShaderBuilder::Build(const std::string& _path, RawShader& _raw, ShaderDescriptor& _desc) const
	{
		if (!mCompiler.Compile(_path, _raw, _desc))
			return false;

		if (!mReflector.Reflect(_raw, _desc))
			return false;

		return true;
	}
}
