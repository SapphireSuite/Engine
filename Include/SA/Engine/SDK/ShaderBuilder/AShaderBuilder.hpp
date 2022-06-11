// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_ASHADER_BUILDER_GUARD
#define SAPPHIRE_ENGINE_ASHADER_BUILDER_GUARD

#include <string>

namespace SA
{
	struct RawShader;
	struct ShaderDescriptor;
	
	namespace SDK
	{
		class AShaderBuilder
		{
		public:
			virtual ~AShaderBuilder() = default;

			/**
			*	Build Shader script in file at _path.
			*
			*	\param[in] _path	shader script file path.
			*	\param[out] _raw	output raw shader data.
			*	\param[out] _desc	output shader descriptor.
			* 
			*	\returns true on build success.
			*/
			virtual bool Build(const std::string& _path, RawShader& _raw, ShaderDescriptor& _desc) const = 0;
		};
	}
}

#endif // GUARD
