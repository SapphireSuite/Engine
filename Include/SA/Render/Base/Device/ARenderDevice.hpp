// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ARENDER_DEVICE_GUARD
#define SAPPHIRE_RENDER_ARENDER_DEVICE_GUARD

#include <SA/Render/Base/Device/AGraphicDeviceInfos.hpp>

namespace Sa
{
	class ARenderDevice
	{
	public:
		virtual void Create(const AGraphicDeviceInfos& _infos) = 0;
		virtual void Destroy() = 0;

		virtual void WaitIdle() const = 0;
	};
}

#endif // GUARD
