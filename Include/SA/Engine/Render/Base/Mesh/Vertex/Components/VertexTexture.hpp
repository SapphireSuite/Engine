// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VERTEX_TEXTURE_GUARD
#define SAPPHIRE_ENGINE_VERTEX_TEXTURE_GUARD

#include <SA/Engine/Render/Base/Mesh/Vertex/Components/VertexComponent.hpp>

#include <SA/Maths/Space/Vector2.hpp>

namespace SA
{
	struct VertexTexture
	{
		Vec2f texture;

		static constexpr Format format = Format(FormatType::R32G32, FormatFlags::Float);
	};
}

#endif // GUARD
