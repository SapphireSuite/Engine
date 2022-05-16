// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_POLYGON_MODE_GUARD
#define SAPPHIRE_ENGINE_POLYGON_MODE_GUARD

#include <SA/Support/API/Vulkan.hpp>

namespace SA
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

	namespace VK
	{
		VkPolygonMode API_GetPolygonMode(PolygonMode _mode) noexcept;
	}

#endif
}

#endif // GUARD
