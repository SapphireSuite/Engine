// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_PIPELINE_RENDER_MODES_GUARD
#define SAPPHIRE_RENDER_PIPELINE_RENDER_MODES_GUARD

#include <SA/Render/Base/Pipeline/Modes/CullingMode.hpp>
#include <SA/Render/Base/Pipeline/Modes/FrontFaceMode.hpp>
#include <SA/Render/Base/Pipeline/Modes/PolygonMode.hpp>

namespace Sa
{
	struct PipelineRenderModes
	{
		PolygonMode polygon = PolygonMode::Fill;
		CullingMode culling = CullingMode::Back;
		FrontFaceMode frontFace = FrontFaceMode::Clockwise;
	};
}

#endif // GUARD
