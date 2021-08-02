// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_CORE_VULKAN_API_GUARD
#define SAPPHIRE_CORE_VULKAN_API_GUARD


#ifndef SA_VULKAN

	/// Sapphire Engine enable Vulkan preprocessor.
	#define SA_VULKAN 0

#endif


#if SA_VULKAN

	#include <vulkan/vulkan.h>

#endif


#endif // GUARD
