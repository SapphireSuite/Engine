// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ARENDER_INTERFACE_GUARD
#define SAPPHIRE_RENDER_ARENDER_INTERFACE_GUARD

#include <SA/Render/Base/ARenderGraphicInterface.hpp>

namespace Sa
{
	class AWindowInterface;
	class AWindow;

	class ARenderInterface
	{
	public:
		virtual ~ARenderInterface() = default;

		virtual void Create(const AWindowInterface* _winIntf) = 0;
		virtual void Destroy() = 0;

		virtual ARenderGraphicInterface* CreateGraphicInterface(const AGraphicDeviceInfos& _infos) = 0;
		virtual void DestroyGraphicInterface(ARenderGraphicInterface* _graphics);

#if SA_WINDOW

		//virtual AWindowSurface* CreateWindowSurface(AWindow* _win) = 0;
		//virtual void DestroyWindowSurface(AWindow* _win, AWindowSurface* _winSurface) = 0;

#endif
	};
}

#endif // GUARD
