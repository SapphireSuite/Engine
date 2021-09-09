// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VERTEX_COMP_GUARD
#define SAPPHIRE_RENDER_VERTEX_COMP_GUARD

#include <SA/Core/Types/Variadics/Flags.hpp>

namespace Sa
{
	enum class VertexComp : uint8
	{
		None = 0,

		Position = 1 << 0,

		Normal = 1 << 1,

		Tangent = 1 << 2,

		Texture = 1 << 3,

		Color = 1 << 4,


		// === Groups ===
		PN = Position | Normal,
		PTex = Position | Texture,
		PC = Position | Color,

		PNTan = Position | Normal | Tangent,
		PNTex = Position | Normal | Texture,
		PNC = Position | Normal | Color,

		PNTanTex = Position | Normal | Tangent | Texture,
		PNTanC = Position | Normal | Tangent | Color,

		Default = PNTanTex,
	};

	SA_DEFINE_ENUM_FLAGS(VertexComp);
}

#endif // GUARD
