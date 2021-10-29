// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ATEXTURE_GUARD
#define SAPPHIRE_RENDER_ATEXTURE_GUARD

#include <SA/Core/Types/Variadics/SparseVector.hpp>

#include <SA/Render/Base/Texture/RawTexture.hpp>

namespace Sa
{
	class ATexture
	{
	};

	using TextureHandle = SparseVectorHandle<ATexture>;
}

#endif // GUARD
