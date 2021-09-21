// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RAW_SHADER_GUARD
#define SAPPHIRE_RENDER_RAW_SHADER_GUARD

#include <vector>

#include <SA/Render/Base/Shader/ShaderStage.hpp>
#include <SA/Render/Base/Shader/Bindings/ShaderBindingDescriptor.hpp>

namespace Sa
{
	struct RawShader
	{
		ShaderStage stage = ShaderStage::Unknown;

		std::vector<uint32> data;
		std::vector<ShaderBindingDescriptor> bindings;

		void Reset();
	};
}

#endif // GUARD
