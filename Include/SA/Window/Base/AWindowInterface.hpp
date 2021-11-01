// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_WINDOW_AWINDOW_INTERFACE_GUARD
#define SAPPHIRE_WINDOW_AWINDOW_INTERFACE_GUARD

#include <vector>

namespace Sa
{
	class AWindow;
	struct WindowCreateInfos;

	class AWindowInterface
	{
	public:
		virtual void Create() = 0;
		virtual void Destroy() = 0;

		virtual AWindow* CreateWindow(const WindowCreateInfos& _infos) = 0;
		virtual void DestroyWindow(AWindow* _window) = 0;

		virtual bool QueryRequiredExtensions(std::vector<const char*>& _extensions) const;
	};
}

#endif // GUARD
