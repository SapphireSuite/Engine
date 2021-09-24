// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ARENDER_SYSTEM_GUARD
#define SAPPHIRE_RENDER_ARENDER_SYSTEM_GUARD

#include <SA/Core/Types/Abstract.hpp>

namespace Sa
{
	class AWindowSystem;
	class AWindow;

	class ARenderDevice;
	struct AGraphicDeviceInfos;

	class ARenderSurface;

	class ARenderSystem : public Abstract
	{
	public:
		virtual void Create(const AWindowSystem& _winSys) = 0;
		virtual void Destroy() = 0;

		virtual ARenderDevice* CreateDevice(const AGraphicDeviceInfos& _infos) = 0;
		virtual void DestroyDevice(ARenderDevice* _device) = 0;

		virtual ARenderSurface* CreateWindowSurface(AWindow& _win);
		virtual void DestroyWindowSurface(AWindow& _win, ARenderSurface*& _surface);
	};
}

#endif // GUARD
