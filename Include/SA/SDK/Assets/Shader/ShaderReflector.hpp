// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_SDK_SHADER_REFLECTOR_GUARD
#define SAPPHIRE_SDK_SHADER_REFLECTOR_GUARD

#include <SA/Render/Base/Shader/RawShader.hpp>

namespace Sa
{
	class ShaderReflector
	{
	public:
		bool Reflect(RawShader& _raw);
	};
}

#endif // GUARD
