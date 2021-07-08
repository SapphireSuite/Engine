// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_WINDOW_WINDOW_MODE_GUARD
#define SAPPHIRE_WINDOW_WINDOW_MODE_GUARD

#include <SA/Core/Types/Int.hpp>

namespace Sa
{
	enum class WindowMode : uint8
	{
		Windowed = 1,
		FullScreen,
		Borderless,
	};
}

#endif // GUARD
