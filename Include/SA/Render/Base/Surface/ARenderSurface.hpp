// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ARENDER_SURFACE_GUARD
#define SAPPHIRE_RENDER_ARENDER_SURFACE_GUARD

#include <SA/Render/Base/Misc/Format.hpp>

namespace Sa
{
	class ARenderSurface
	{
	protected:
		~ARenderSurface() = default;

	public:
		virtual Format GetFormat() const = 0;
	};
}

#endif // GUARD
