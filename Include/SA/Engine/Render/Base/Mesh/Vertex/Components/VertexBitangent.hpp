// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VERTEX_BITANGENT_GUARD
#define SAPPHIRE_ENGINE_VERTEX_BITANGENT_GUARD

#include <SA/Engine/Render/Base/Mesh/Vertex/Components/VertexComponent.hpp>

#include <SA/Maths/Space/Vector3.hpp>

namespace SA
{
	struct VertexBitangent
	{
		Vec3f bitangent;
		
		static constexpr Format format = Format(FormatType::R32G32B32, FormatFlags::Float);
	};
}

#endif // GUARD
