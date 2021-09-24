// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <SA/Render/Vulkan/Surface/VkSurfaceSupportDetails.hpp>

namespace Sa::Vk
{
	VkSurfaceFormatKHR SurfaceSupportDetails::ChooseSwapSurfaceFormat() const
	{
		// Prefered
		for (uint32 i = 0; i < formats.size(); ++i)
		{
			if (formats[i].format == VK_FORMAT_B8G8R8A8_SRGB && formats[i].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
				return formats[i];
		}

		// Default.
		return formats[0];
	}

	VkPresentModeKHR SurfaceSupportDetails::ChooseSwapPresentMode() const
	{
		// Prefered.
		for (uint32 i = 0; i < presentModes.size(); ++i)
		{
			if (presentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR)
				return presentModes[i];
		}

		// Default FIFO always supported.
		return VK_PRESENT_MODE_FIFO_KHR;
	}

	Vec2ui SurfaceSupportDetails::ChooseSwapExtent() const
	{
		if (capabilities.currentExtent.width != UINT32_MAX)
			return Vec2ui(capabilities.currentExtent.width, capabilities.currentExtent.height);
		else
		{
			// TODO: Clean.
			Vec2ui actualExtent = { 1920, 1080 };

			actualExtent.x = std::clamp(actualExtent.x, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
			actualExtent.y = std::clamp(actualExtent.y, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

			return actualExtent;
		}
	}
}
