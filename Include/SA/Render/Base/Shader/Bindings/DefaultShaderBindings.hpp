// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DEFAULT_SHADER_BINDINGS_GUARD
#define SAPPHIRE_RENDER_DEFAULT_SHADER_BINDINGS_GUARD

#include <SA/Core/Types/Int.hpp>

namespace Sa
{
	constexpr uint32 engineDescriptorSet = 1;

	enum class ShaderBindingID : uint32
	{
		Camera = 0,
		Model = 1,
	};
}

#endif // GUARD
