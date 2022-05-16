// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_CULLING_MODE_GUARD
#define SAPPHIRE_ENGINE_CULLING_MODE_GUARD

#include <SA/Support/API/Vulkan.hpp>

namespace SA
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
	
	namespace VK
	{
		VkCullModeFlags API_GetCullingMode(CullingMode _mode) noexcept;
	}

#endif
}

#endif // GUARD
