// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ARENDER_PIPELINE_GUARD
#define SAPPHIRE_RENDER_ARENDER_PIPELINE_GUARD

#include <SA/Render/Base/ARenderResource.hpp>

#include <SA/Render/Base/Pipeline/RenderPipelineDescriptor.hpp>

namespace Sa
{
	class ARenderDevice;
	class ARenderFrame;

	class ARenderPipeline : public ARenderResource
	{
	public:
		virtual void Create(const ARenderDevice* _device, const RenderPipelineDescriptor& _desc) = 0;
		virtual void Destroy(const ARenderDevice* _device) = 0;

		virtual void Bind(const ARenderFrame& _frame) const = 0;
	};
}

#endif // GUARD
