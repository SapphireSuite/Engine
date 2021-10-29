// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ACUBEMAP_GUARD
#define SAPPHIRE_RENDER_ACUBEMAP_GUARD

#include <SA/Core/Types/Variadics/SparseVector.hpp>

#include <SA/Render/Base/Texture/RawCubemap.hpp>

namespace Sa
{
	class ACubemap
	{
	};

	using CubemapHandle = SparseVectorHandle<ACubemap>;
}

#endif // GUARD
