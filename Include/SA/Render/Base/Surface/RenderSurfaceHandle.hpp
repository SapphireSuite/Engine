// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RENDER_SURFACE_HANDLE_GUARD
#define SAPPHIRE_RENDER_RENDER_SURFACE_HANDLE_GUARD

#include <SA/Core/Types/Handle.hpp>

#include <SA/Render/Base/Misc/Format.hpp>

namespace Sa
{
	struct RenderSurfaceHandle : public Handle
	{
		using Handle::Handle;

		Format format;
	};
}

#endif // GUARD