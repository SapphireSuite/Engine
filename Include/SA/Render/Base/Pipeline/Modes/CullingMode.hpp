// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_CULLING_MODE_GUARD
#define SAPPHIRE_RENDER_CULLING_MODE_GUARD

#include <SA/Core/Support/API/Vulkan.hpp>

namespace Sa
{
	enum class CullingMode
	{
		// No culling.
		None,

		// Front-face culling.
		Front,

		// Back-face culling.
		Back,
	};


#if SA_VULKAN
	
	namespace Vk
	{
		VkCullModeFlags API_GetCullingMode(CullingMode _mode) noexcept;
	}

#endif
}

#endif // GUARD
