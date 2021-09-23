// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_RENDER_SURFACE_SUPPORT_DETAILS_GUARD
#define SAPPHIRE_RENDER_VK_RENDER_SURFACE_SUPPORT_DETAILS_GUARD

#include <vector>

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Core/Support/API/Vulkan.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	struct RenderSurfaceSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;

		VkSurfaceFormatKHR ChooseSwapSurfaceFormat() const;
		VkPresentModeKHR ChooseSwapPresentMode() const;
		Vec2ui ChooseSwapExtent() const;
	};
}

#endif

#endif // GUARD
