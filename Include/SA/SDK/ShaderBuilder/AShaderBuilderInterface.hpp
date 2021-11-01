// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ASHADER_BUILDER_INTERFACE_GUARD
#define SAPPHIRE_RENDER_ASHADER_BUILDER_INTERFACE_GUARD

#include <string>

namespace Sa
{
	struct RawShader;
	struct ShaderDescriptor;

	class AShaderBuilderInterface
	{
	public:
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

#endif // GUARD
