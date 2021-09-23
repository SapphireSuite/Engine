// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_WINDOW_CURSOR_MODE_GUARD
#define SAPPHIRE_WINDOW_CURSOR_MODE_GUARD

#include <SA/Core/Types/Variadics/Flags.hpp>

namespace Sa
{
	enum class CursorMode : uint8
	{
		None = 0,

		Capture = 1 << 0,

		Hidden = 1 << 1,
	};

	SA_DEFINE_ENUM_FLAGS(CursorMode);
}

#endif // GUARD
