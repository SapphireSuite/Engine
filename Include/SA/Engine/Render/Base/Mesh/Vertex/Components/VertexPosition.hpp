// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VERTEX_POSITION_GUARD
#define SAPPHIRE_ENGINE_VERTEX_POSITION_GUARD

#include <SA/Engine/Render/Base/Mesh/Vertex/Components/VertexComponent.hpp>

#include <SA/Maths/Space/Vector3.hpp>

namespace SA
{
	struct VertexPosition
	{
		Vec3f position;

		static constexpr Format format = Format(FormatType::R32G32B32, FormatFlags::Float);
	};
}

#endif // GUARD
