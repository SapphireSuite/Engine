// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RAW_SHADER_GUARD
#define SAPPHIRE_RENDER_RAW_SHADER_GUARD

#include <SA/Render/Base/Shader/ShaderDescriptor.hpp>

namespace Sa
{
	struct RawShader
	{
		std::vector<uint32> data;
		ShaderDescriptor descriptor;

		void Reset();
	};
}

#endif // GUARD
