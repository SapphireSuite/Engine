// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_ARENDER_DEVICE_GUARD
#define SAPPHIRE_ENGINE_ARENDER_DEVICE_GUARD

#include <SA/Engine/Render/Base/Context/ARenderContext.hpp>

namespace SA
{
	class ARenderDevice : protected HardwareInterface
	{
	public:
		virtual void WaitIdle() const = 0;

		virtual ARenderContext* CreateRenderContext() = 0;
		virtual void DestroyRenderContext(ARenderContext* _context) = 0;
	};
}

#endif // GUARD
