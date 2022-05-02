// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_WINDOW_SURFACE_GUARD
#define SAPPHIRE_ENGINE_VK_WINDOW_SURFACE_GUARD

#include <SA/Support/API/Vulkan.hpp>

#include <SA/Engine/Render/Base/Surface/AWindowSurface.hpp>
#include <SA/Engine/Render/Vulkan/Surface/VkWindowSurfaceHandle.hpp>

namespace Sa::Vk
{
	class Instance;

    class WindowSurface : public AWindowSurface
	{
		WindowSurfaceHandle mHandle = VK_NULL_HANDLE;

		using AWindowSurface::Create;
		using AWindowSurface::Destroy;

	public:
		void Create(AWindow* _win,  const Instance& _inst);
		void Destroy(const Instance& _inst);

		operator VkSurfaceKHR() const;
	};


	struct WindowSurfaceDestroyer
	{
		Instance& intf;

		void operator()(WindowSurface& _in)
		{
			_in.Destroy(intf);
		}
	};
}

#endif // GUARD
