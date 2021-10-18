// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_GLSL_SHADER_REFLECTOR_GUARD
#define SAPPHIRE_RENDER_GLSL_SHADER_REFLECTOR_GUARD

namespace Sa
{
	struct RawShader;
	struct ShaderDescriptor;

	namespace GLSL
	{
		class ShaderReflector
		{
		public:
			bool Reflect(RawShader& _raw, ShaderDescriptor& _desc);
		};
	}
}

#endif // GUARD
