// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_ARENDER_INTERFACE_GUARD
#define SAPPHIRE_ENGINE_ARENDER_INTERFACE_GUARD

#include <SA/Engine/HI/HardwareInterface.hpp>

#include <SA/Engine/Render/Base/Surface/AWindowSurface.hpp>

namespace Sa
{
	class AWindowInterface;
	class AWindow;

	class ARenderInterface : protected HardwareInterface
	{	
        using HardwareInterface::Create;

	public:
    	/**
		*	Virtual destructor.
		*	Ensure correct polymorphism destruction.
		*/
		virtual ~ARenderInterface() = default;

		virtual void Create(const AWindowInterface* _winIntf = nullptr);
        using HardwareInterface::Destroy;
        using HardwareInterface::Clear;

		// virtual ARenderGraphicInterface* CreateGraphicInterface(const AGraphicDeviceInfos& _infos) = 0;
		// virtual void DestroyGraphicInterface(ARenderGraphicInterface* _graphics);

#if SA_WINDOW

		virtual AWindowSurface* CreateWindowSurface(AWindow* _win) = 0;
		virtual void DestroyWindowSurface(AWindowSurface* _winSurface) = 0;

#endif
	};
}

#endif // GUARD
