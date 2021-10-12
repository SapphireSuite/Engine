// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ARENDER_INTERFACE_GUARD
#define SAPPHIRE_RENDER_ARENDER_INTERFACE_GUARD

#include <SA/Core/Types/Abstract.hpp>

#include <SA/Render/Base/ARenderSubInterface.hpp>

namespace Sa
{
	class AWindowInterface;
	class AWindow;

	class ARenderInterface : public Abstract
	{
	public:
		virtual void Create(const AWindowInterface* _winIntf) = 0;
		virtual void Destroy() = 0;

		virtual ARenderSubInterface* CreateSubInterface(const AGraphicDeviceInfos& _infos) = 0;
		virtual void DestroySubInterface(ARenderSubInterface* _intf);

		virtual ARenderSurface* MakeWindowSurface(AWindow* _win) = 0;
		virtual void DestroyWindowSurface(AWindow* _win, ARenderSurface* _surface) = 0;
	};
}

#endif // GUARD
