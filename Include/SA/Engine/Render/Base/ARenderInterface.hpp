// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_ARENDER_INTERFACE_GUARD
#define SAPPHIRE_ENGINE_ARENDER_INTERFACE_GUARD

#include <vector>

#include <SA/Engine/Render/Base/Device/ARenderDevice.hpp>
#include <SA/Engine/Render/Base/Device/ARenderDeviceInfos.hpp>

#include <SA/Engine/Render/Base/Surface/AWindowSurface.hpp>

namespace Sa
{
	class AWindowInterface;
	class AWindow;

	class ARenderInterface : protected HardwareInterface
	{	
        using HardwareInterface::Create; // overloaded.

	public:
		virtual void Create(const AWindowInterface* _winIntf = nullptr);
        using HardwareInterface::Destroy;
        using HardwareInterface::Clear;

		/**
		 * @brief Query supported devices for rendering.
		 * 
		 * @param _winSurface	Assossiated window surface requiered for window presenting. Null for offscreen rendering. 
		 * @return std::vector<ARenderDeviceInfos*> supported render device infos.
		 */
		virtual std::vector<ARenderDeviceInfos*> QueryDevices(AWindowSurface* _winSurface = nullptr) = 0;
		virtual ARenderDevice* CreateDevice(ARenderDeviceInfos* _infos) = 0;
		virtual void DestroyDevice(ARenderDevice* _device) = 0;

#if SA_WINDOW

		virtual AWindowSurface* CreateWindowSurface(AWindow* _win) = 0;
		virtual void DestroyWindowSurface(AWindowSurface* _winSurface) = 0;

#endif
	};
}

#endif // GUARD
