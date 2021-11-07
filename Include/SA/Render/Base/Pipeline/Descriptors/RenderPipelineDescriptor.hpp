// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RENDER_PIPELINE_DESCRIPTOR_GUARD
#define SAPPHIRE_RENDER_RENDER_PIPELINE_DESCRIPTOR_GUARD

#include <SA/Render/Base/Pipeline/Descriptors/PipelineRenderPassInfos.hpp>
#include <SA/Render/Base/Pipeline/Descriptors/PipelineShaderInfos.hpp>
#include <SA/Render/Base/Pipeline/Modes/PipelineRenderModes.hpp>

namespace Sa
{
	struct RenderPipelineDescriptor
	{
		/// Bound RenderPass infos.
		PipelineRenderPassInfos passInfos;

		/// Bound shader infos.
		PipelineShaderInfos shaderInfos;

		/// Rendering modes.
		PipelineRenderModes modes;
	};
}

#endif // GUARD
