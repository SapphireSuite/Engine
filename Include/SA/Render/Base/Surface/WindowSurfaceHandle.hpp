// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_WINDOW_SURFACE_HANDLE_GUARD
#define SAPPHIRE_RENDER_WINDOW_SURFACE_HANDLE_GUARD

#include <SA/Core/Types/Handle.hpp>

#include <SA/Core/Support/API/Vulkan.hpp>

namespace Sa
{
	struct WindowSurfaceHandle : public Handle
	{
		using Handle::Handle;

#if SA_VULKAN

		WindowSurfaceHandle(VkSurfaceKHR _vkHandle) noexcept;

		operator VkSurfaceKHR() const;

#endif
	};
}

#endif // GUARD
