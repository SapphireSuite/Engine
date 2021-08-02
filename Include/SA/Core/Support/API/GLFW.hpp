// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_GLFW_API_GUARD
#define SAPPHIRE_CORE_GLFW_API_GUARD


#ifndef SA_GLFW

	/// Sapphire Engine enable GLFW preprocessor.
	#define SA_GLFW 0

#endif


#if SA_GLFW

	// Include Vulkan before GLFW (if enabled).
	#include <SA/Core/Support/API/Vulkan.hpp>

	#include <GLFW/glfw3.h>

#endif


#endif // GUARD
