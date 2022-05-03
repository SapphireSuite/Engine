// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_RENDER_VULKAN_DEBUG_GUARD
#define SAPPHIRE_ENGINE_RENDER_VULKAN_DEBUG_GUARD

#include <SA/Collections/Debug>

#include <SA/Engine/Render/Vulkan/Debug/Exception_Vulkan.hpp>
#include <SA/Engine/Render/Vulkan/Debug/VkValidationLayers.hpp>

#define SA_VK_ASSERT(_pred, ...) SA_ASSERT_EXEC(Vulkan, SA/Engine/Render/Vulkan, (_pred), ##__VA_ARGS__)

#endif // GUARD
