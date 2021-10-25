// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_WINDOW_SURFACE_GUARD
#define SAPPHIRE_RENDER_VK_WINDOW_SURFACE_GUARD

#include <SA/Core/Support/API/Vulkan.hpp>

namespace Sa::Vk
{
	class WindowSurface
	{
		VkSurfaceKHR mHandle = VK_NULL_HANDLE;

	public:
		WindowSurface(VkSurfaceKHR _handle) noexcept;

		operator VkSurfaceKHR() const;
	};
}

#endif // GUARD
