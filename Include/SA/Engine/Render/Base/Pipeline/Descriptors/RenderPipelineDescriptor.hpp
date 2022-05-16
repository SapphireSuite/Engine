// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_RENDER_PIPELINE_DESCRIPTOR_GUARD
#define SAPPHIRE_ENGINE_RENDER_PIPELINE_DESCRIPTOR_GUARD

#include <SA/Engine/Render/Base/Pipeline/Descriptors/PipelineRenderPassInfos.hpp>
#include <SA/Engine/Render/Base/Pipeline/Descriptors/PipelineShaderInfos.hpp>
#include <SA/Engine/Render/Base/Pipeline/Modes/PipelineRenderModes.hpp>

namespace SA
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
