// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_GLSL_SHADER_REFLECTOR_GUARD
#define SAPPHIRE_ENGINE_GLSL_SHADER_REFLECTOR_GUARD

namespace SA
{
	struct RawShader;
	struct ShaderDescriptor;

	namespace SDK::GLSL
	{
		class ShaderReflector
		{
		public:
			bool Reflect(const RawShader& _raw, ShaderDescriptor& _desc) const;
		};
	}
}

#endif // GUARD
