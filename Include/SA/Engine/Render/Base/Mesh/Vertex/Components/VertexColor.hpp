// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VERTEX_COLOR_GUARD
#define SAPPHIRE_ENGINE_VERTEX_COLOR_GUARD

#include <SA/Engine/Render/Base/Mesh/Vertex/Components/VertexComponent.hpp>

#include <SA/Engine/Render/Base/Misc/Color.hpp>

namespace SA
{
	struct VertexColor
	{
		Color color;

		static constexpr Format format = Format(FormatType::R32G32B32A32, FormatFlags::Float);
	};
}

#endif // GUARD
