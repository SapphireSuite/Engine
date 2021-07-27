// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VULKAN_GUARD
#define SAPPHIRE_RENDER_VULKAN_GUARD

#include <SA/Render/Config.hpp>

#include <SA/Core/Debug/Debug.hpp>


#if SA_VULKAN


	#include <vulkan/vulkan.h>


	#define SA_VK_VALIDATION_LAYERS (SA_DEBUG || __SA_LOG_RELEASE) && 1


	#define SA_VK_ASSERT(_pred, ...) SA_ASSERT_EXEC(Vulkan, SA/Render/Vulkan, (_pred), ##__VA_ARGS__)


#endif


#endif // GUARD
