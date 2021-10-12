// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Surface/VkWindowSurface.hpp>

namespace Sa::Vk
{
	WindowSurface::WindowSurface(VkSurfaceKHR _handle) noexcept :
		mHandle{ _handle }
	{
	}

	WindowSurface::operator VkSurfaceKHR() const
	{
		return mHandle;
	}
}
