// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ATEXTURE_GUARD
#define SAPPHIRE_RENDER_ATEXTURE_GUARD

#include <SA/Core/Types/Abstract.hpp>

#include <SA/Render/Base/Texture/RawTexture.hpp>

namespace Sa
{
	class ARenderDevice;
	class ARenderResourceInitializer;

	class ATexture : public Abstract
	{
	public:
		virtual void Create(ARenderResourceInitializer* _init, const RawTexture& _raw) = 0;
		virtual void Destroy(const ARenderDevice* _device) = 0;
	};
}

#endif // GUARD
