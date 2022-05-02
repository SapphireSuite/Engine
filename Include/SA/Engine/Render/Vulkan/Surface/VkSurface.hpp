// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_SURFACE_GUARD
#define SAPPHIRE_ENGINE_VK_SURFACE_GUARD

#include <SA/Engine/Render/Base/Surface/ARenderSurface.hpp>

namespace Sa::Vk
{
	class Device;
	class WindowSurface;

	class Surface : public ARenderSurface
	{
		using HardwareInterface::Create; // overloaded.
		using HardwareInterface::Destroy;// overloaded.

	public:
		void Create(const Device& _device, const WindowSurface& _winSurface);
		void Destroy(const Device& _device);
	};
}

#endif // GUARD
