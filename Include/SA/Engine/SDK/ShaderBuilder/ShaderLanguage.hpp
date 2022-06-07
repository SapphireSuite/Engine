// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_SHADER_LANGUAGE_GUARD
#define SAPPHIRE_ENGINE_SHADER_LANGUAGE_GUARD

namespace SA::SDK
{
	enum class ShaderLanguage
	{
	#if SA_VULKAN || SA_OPEN_GL

		GLSL,

		HLSL,

	#endif
	};
}

#endif // GUARD
