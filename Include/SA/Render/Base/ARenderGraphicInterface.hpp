// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ARENDER_GRAPHIC_INTERFACE_GUARD
#define SAPPHIRE_RENDER_ARENDER_GRAPHIC_INTERFACE_GUARD

#include <SA/Render/Base/Device/ARenderDevice.hpp>
#include <SA/Render/Base/ARenderContextInterface.hpp>

namespace Sa
{
	class ARenderGraphicInterface
	{
	public:
		virtual ~ARenderGraphicInterface() = default;

		virtual const ARenderDevice* GetDevice() const = 0;

		virtual void Create(const AGraphicDeviceInfos& _infos) = 0;
		virtual void Destroy() = 0;

		virtual ARenderContextInterface* CreateContextInterface() = 0;
		virtual void DestroyContextInterface(ARenderContextInterface* _context);
	};
}

#endif // GUARD
