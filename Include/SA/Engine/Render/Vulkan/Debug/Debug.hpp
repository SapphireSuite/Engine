// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_RENDER_VULKAN_DEBUG_GUARD
#define SAPPHIRE_ENGINE_RENDER_VULKAN_DEBUG_GUARD

#include <SA/Collections/Debug>

#include <SA/Engine/Render/Vulkan/Debug/Exception_Vulkan.hpp>

#define SA_VK_VALIDATION_LAYERS SA_VULKAN && (SA_DEBUG || SA_LOG_RELEASE_OPT) && 1

#define SA_VK_ASSERT(_pred, ...) SA_ASSERT_EXEC(Vulkan, SA/Render/Vulkan, (_pred), ##__VA_ARGS__)

#endif // GUARD
