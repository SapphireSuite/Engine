// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COLOR_GUARD
#define SAPPHIRE_RENDER_COLOR_GUARD

#include <SA/Support/API/Vulkan.hpp>

namespace Sa
{
	struct Color
	{
		float r = 0.0f;
		float g = 0.0f;
		float b = 0.0f;
		float a = 1.0f;

		static const Color red;
		static const Color green;
		static const Color blue;
		static const Color black;
		static const Color white;

#if SA_VULKAN

		operator VkClearValue() const noexcept;
		operator VkClearColorValue() const noexcept;

#endif
	};
}

#endif // GUARD
