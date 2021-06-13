// Copyright 2020 Sapphire development team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_KEY_STATE_GUARD
#define SAPPHIRE_INPUT_INPUT_KEY_STATE_GUARD

#include <SA/Core/Types/Int.hpp>

namespace Sa
{
	enum class InputKeyState : uint8
	{
		Pressed = 1,
		Released,
	};
}

#endif // GUARD
