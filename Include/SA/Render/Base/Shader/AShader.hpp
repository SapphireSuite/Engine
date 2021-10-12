// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma	once

#ifndef SAPPHIRE_RENDER_ASHADER_GUARD
#define SAPPHIRE_RENDER_ASHADER_GUARD

#include <SA/Render/Base/ARenderResource.hpp>

#include <SA/Render/Base/Shader/RawShader.hpp>

namespace Sa
{
	class ARenderDevice;
	class ARenderResourceInitializer;

	class AShader : public ARenderResource
	{
	public:
		virtual void Create(ARenderResourceInitializer* _init, const RawShader& _raw) = 0;
		virtual void Destroy(const ARenderDevice* _device) = 0;
	};
}

#endif // GUARD
