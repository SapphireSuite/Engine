// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/Surface/WindowSurfaceHandle.hpp>

namespace Sa
{
#if SA_VULKAN

	WindowSurfaceHandle::WindowSurfaceHandle(VkSurfaceKHR _vkHandle) noexcept :
		Handle(reinterpret_cast<uint64>(_vkHandle))
	{
	}

	WindowSurfaceHandle::operator VkSurfaceKHR() const
	{
		return reinterpret_cast<VkSurfaceKHR>(ID);
	}

#endif
}
