// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VULKAN_DEBUG_GUARD
#define SAPPHIRE_RENDER_VULKAN_DEBUG_GUARD

#include <SA/Core/Debug.hpp>

#include <SA/Core/Support/API/Vulkan.hpp>

#if SA_VULKAN

	#include <SA/Render/Vulkan/Debug/Exception_Vulkan.hpp>

	#define SA_VK_VALIDATION_LAYERS SA_VULKAN && (SA_DEBUG || __SA_LOG_RELEASE) && 1

	#define SA_VK_ASSERT(_pred, ...) SA_ASSERT_EXEC(Vulkan, SA/Render/Vulkan, (_pred), ##__VA_ARGS__)

#endif

#endif // GUARD
