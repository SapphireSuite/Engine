// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_PIPELINE_RENDER_MODES_GUARD
#define SAPPHIRE_ENGINE_PIPELINE_RENDER_MODES_GUARD

#include <SA/Engine/Render/Base/Pipeline/Modes/CullingMode.hpp>
#include <SA/Engine/Render/Base/Pipeline/Modes/FrontFaceMode.hpp>
#include <SA/Engine/Render/Base/Pipeline/Modes/PolygonMode.hpp>

namespace SA
{
	struct PipelineRenderModes
	{
		PolygonMode polygon = PolygonMode::Fill;
		CullingMode culling = CullingMode::Back;
		FrontFaceMode frontFace = FrontFaceMode::Clockwise;
	};
}

#endif // GUARD
