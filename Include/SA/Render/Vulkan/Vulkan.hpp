// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VULKAN_GUARD
#define SAPPHIRE_RENDER_VULKAN_GUARD

#include <SA/Collections/Debug>

// TODO: Add if compilation.
/// Sapphire Engine enable Vulkan preprocessor.
#define SA_VULKAN 1

#if SA_VULKAN


	#include <vulkan/vulkan.h>


	#define SA_VK_VALIDATION_LAYERS (SA_DEBUG || __SA_LOG_RELEASE) && 1


	#define SA_VK_ASSERT(_pred, ...) SA_ASSERT_EXEC(Default, SA/Render/Vulkan, (_pred) == VkResult::VK_SUCCESS, ##__VA_ARGS__)


	namespace Sa::Vk
	{
		SA_ENGINE_API void Init();
		SA_ENGINE_API void UnInit();
	}

#endif


#endif // GUARD
