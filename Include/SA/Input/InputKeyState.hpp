// Copyright 2020 Sapphire development team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_INPUT_INPUT_KEY_STATE_GUARD
#define SAPPHIRE_INPUT_INPUT_KEY_STATE_GUARD

#include <SA/Core/Types/Int.hpp>

#include <SA/Window/Config.hpp>

#if SA_GLFW

#include <GLFW/glfw3.h>

#endif

namespace Sa
{
	enum class InputKeyState : uint8
	{
#if SA_GLFW

		Pressed = GLFW_PRESS,
		Hold = GLFW_REPEAT,
		Released = GLFW_RELEASE

#endif
	};
}

#endif // GUARD
