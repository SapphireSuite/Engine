// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_MATHS_TRANSFORM_COMP_GUARD
#define SAPPHIRE_MATHS_TRANSFORM_COMP_GUARD

#include <SA/Core/Types/Variadics/Flags.hpp>

namespace Sa
{
	enum class TransformComp : uint8
	{
		None = 0,

		Position = 1 << 0,

		Rotation = 1 << 1,

		Scale = 1 << 2,

		UScale = 1 << 3,


		PR = Position | Rotation,
		PS = Position | Scale,
		PUS = Position | UScale,

		RS = Rotation | Scale,
		RUS = Rotation | UScale,

		PRS = Position | Rotation | Scale,
		PRUS = Position | Rotation | UScale,
	};

	using TrComp = TransformComp;

	SA_DEFINE_ENUM_FLAGS(TransformComp)
}

#endif // GUARD
