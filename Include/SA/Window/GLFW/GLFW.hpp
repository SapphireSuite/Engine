// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_WINDOW_GLFW_GUARD
#define SAPPHIRE_WINDOW_GLFW_GUARD

#include <SA/Window/Config.hpp>

#if SA_GLFW

namespace Sa::GLFW
{
	void Init();
	void UnInit();

	void PollEvents();
}

#endif

#endif // GUARD
