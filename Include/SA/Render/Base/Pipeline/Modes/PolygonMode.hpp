// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_POLYGON_MODE_GUARD
#define SAPPHIRE_RENDER_POLYGON_MODE_GUARD

#include <SA/Core/Support/API/Vulkan.hpp>

namespace Sa
{
	enum class PolygonMode
	{
		// Draw point only.
		Point,

		// Draw line only.
		Line,

		// Draw fill triangle.
		Fill
	};


#if SA_VULKAN

	namespace Vk
	{
		VkPolygonMode API_GetPolygonMode(PolygonMode _mode) noexcept;
	}

#endif
}

#endif // GUARD
