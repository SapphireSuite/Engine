// Copyright 2020 Sapphire development team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_KEY_STATE_GUARD
#define SAPPHIRE_INPUT_KEY_STATE_GUARD

#include <SA/Core/Types/Variadics/Flags.hpp>

namespace Sa
{
	enum class KeyState : uint8
	{
		Pressed = 1 << 0,
		Released = 1 << 1,
		Hold = 1 << 2,
	};

	SA_DEFINE_ENUM_FLAGS(KeyState)
}

#endif // GUARD
