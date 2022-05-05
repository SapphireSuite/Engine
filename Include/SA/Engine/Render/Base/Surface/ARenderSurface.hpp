// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_ARENDER_SURFACE_GUARD
#define SAPPHIRE_ENGINE_ARENDER_SURFACE_GUARD

#include <SA/Engine/HI/HardwareInterface.hpp>

#include <SA/Maths/Space/Vector2.hpp>

#include <SA/Engine/Render/Base/Misc/Format.hpp>

namespace Sa
{
	class AWindowSurface;

	class ARenderSurface : protected HardwareInterface
	{
		using HardwareInterface::Clear; // not used.

	public:
		virtual Vec2ui GetExtent() const = 0;
		virtual Format GetFormat() const = 0;
	};
}

#endif // GUARD
