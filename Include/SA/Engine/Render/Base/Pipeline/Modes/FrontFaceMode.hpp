// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_FRONT_FACE_GUARD
#define SAPPHIRE_ENGINE_FRONT_FACE_GUARD

#include <SA/Support/API/Vulkan.hpp>

namespace SA
{
	enum class FrontFaceMode
	{
		// Clockwise polygon are front-face.
		Clockwise,

		// Counter clockwise polygon are front-face.
		CounterClockwise,
	};


#if SA_VULKAN

	namespace VK
	{
		VkFrontFace API_GetFrontFaceMode(FrontFaceMode _mode) noexcept;
	}

#endif
}

#endif // GUARD
