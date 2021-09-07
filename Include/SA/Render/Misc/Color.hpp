// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_COLOR_GUARD
#define SAPPHIRE_RENDER_COLOR_GUARD

#include <SA/Config.hpp>

#include <SA/Core/Support/API/Vulkan.hpp>

namespace Sa
{
	struct Color
	{
		float r = 0.0f;
		float g = 0.0f;
		float b = 0.0f;
		float a = 1.0f;

		SA_ENGINE_API static const Color red;
		SA_ENGINE_API static const Color green;
		SA_ENGINE_API static const Color blue;
		SA_ENGINE_API static const Color black;
		SA_ENGINE_API static const Color white;

#if SA_VULKAN

		operator VkClearValue() const noexcept;
		operator VkClearColorValue() const noexcept;

#endif
	};
}

#endif // GUARD
