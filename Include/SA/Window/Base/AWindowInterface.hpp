// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_WINDOW_AWINDOW_INTERFACE_GUARD
#define SAPPHIRE_WINDOW_AWINDOW_INTERFACE_GUARD

#include <SA/Core/Types/Abstract.hpp>

namespace Sa
{
	class AWindow;
	struct WindowCreateInfos;

	class AWindowInterface : public Abstract
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
