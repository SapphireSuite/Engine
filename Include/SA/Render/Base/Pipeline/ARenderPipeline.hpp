// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ARENDER_PIPELINE_GUARD
#define SAPPHIRE_RENDER_ARENDER_PIPELINE_GUARD

#include <SA/Render/Base/Pipeline/RenderPipelineDescriptor.hpp>

namespace Sa
{
	class ARenderFrame;

	class ARenderPipeline
	{
	public:
		virtual void Bind(const ARenderFrame& _frame) const = 0;
	};
}

#endif // GUARD
