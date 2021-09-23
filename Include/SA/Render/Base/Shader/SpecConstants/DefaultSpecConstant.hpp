// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DEFAULT_SPEC_CONSTANT_GUARD
#define SAPPHIRE_RENDER_DEFAULT_SPEC_CONSTANT_GUARD

#include <SA/Core/Types/Int.hpp>

namespace Sa
{
	enum SpecConstantID : uint8
	{
		Min = 100,

		RenderAPI = 101,

		Max,
	};


	enum class SpecConstantValue : uint32 // Must be size 32 for correct binding.
	{
		// SpecConstantID::RenderAPI
		
		Vulkan = 1,
		OpenGL = 2,
		DirectX = 3,
	};
}

#endif // GUARD
