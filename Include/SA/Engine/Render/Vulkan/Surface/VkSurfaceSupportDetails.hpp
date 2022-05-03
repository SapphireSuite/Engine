// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_SURFACE_SUPPORT_DETAILS_GUARD
#define SAPPHIRE_ENGINE_VK_SURFACE_SUPPORT_DETAILS_GUARD

#include <vector>

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Support/API/Vulkan.hpp>

namespace Sa::Vk
{
	struct SurfaceSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;

		VkSurfaceFormatKHR ChooseSwapSurfaceFormat() const;
		VkPresentModeKHR ChooseSwapPresentMode() const;
		Vec2ui ChooseSwapExtent() const;
	};
}

#endif // GUARD
