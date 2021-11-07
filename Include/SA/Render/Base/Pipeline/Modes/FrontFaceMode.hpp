// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_FRONT_FACE_GUARD
#define SAPPHIRE_RENDER_FRONT_FACE_GUARD

#include <SA/Core/Support/API/Vulkan.hpp>

namespace Sa
{
	enum class FrontFaceMode
	{
		// Clockwise polygon are front-face.
		Clockwise,

		// Counter clockwise polygon are front-face.
		CounterClockwise,
	};


#if SA_VULKAN

	namespace Vk
	{
		VkFrontFace API_GetFrontFaceMode(FrontFaceMode _mode) noexcept;
	}

#endif
}

#endif // GUARD
