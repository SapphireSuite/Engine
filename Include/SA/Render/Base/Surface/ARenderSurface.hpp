// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ARENDER_SURFACE_GUARD
#define SAPPHIRE_RENDER_ARENDER_SURFACE_GUARD

#include <SA/Render/Base/Misc/Format.hpp>

#include <SA/Core/Types/Variadics/SparseVector.hpp>

namespace Sa
{
	class ARenderSurface
	{
	public:
		virtual Format GetFormat() const = 0;
	};

	using RenderSurfaceHandle = SparseVectorHandle<ARenderSurface>;
}

#endif // GUARD
