// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_CURSOR_MODE_GUARD
#define SAPPHIRE_ENGINE_CURSOR_MODE_GUARD

#include <SA/Flags/Flags.hpp>

namespace SA
{
	enum class CursorMode : uint8_t
	{
		None = 0,

		Capture = 1 << 0,

		Hidden = 1 << 1,
	};

	SA_DEFINE_ENUM_FLAGS(CursorMode);
}

#endif // GUARD
