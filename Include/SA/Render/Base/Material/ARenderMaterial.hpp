// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ARENDER_MATERIAL_GUARD
#define SAPPHIRE_RENDER_ARENDER_MATERIAL_GUARD

#include <SA/Core/Types/Abstract.hpp>

namespace Sa
{
	class ARenderDevice;
	class ARenderPipeline;
	struct RenderPipelineDescriptor;

	class ARenderMaterial : public Abstract
	{
	public:
		virtual void Create(const ARenderDevice* _device,
			const ARenderPipeline* _pipeline,
			const RenderPipelineDescriptor& _desc,
			uint32 setIndex = 0) = 0;
		virtual void Destroy(const ARenderDevice* _device) = 0;
	};
}

#endif // GUARD
