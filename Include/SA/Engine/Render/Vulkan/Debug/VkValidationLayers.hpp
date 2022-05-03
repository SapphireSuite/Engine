// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_RENDER_VK_VALIDATION_LAYES_GUARD
#define SAPPHIRE_ENGINE_RENDER_VK_VALIDATION_LAYES_GUARD

#include <SA/Support/API/Vulkan.hpp>

#define SA_VK_VALIDATION_LAYERS SA_VULKAN && (SA_DEBUG || SA_LOG_RELEASE_OPT) && 1

#if SA_VK_VALIDATION_LAYERS

namespace Sa::Vk
{
	class ValidationLayers
	{
	public:
		~ValidationLayers() = delete;

		static VkDebugUtilsMessengerCreateInfoEXT GetDebugUtilsMessengerCreateInfo() noexcept;

		static uint32_t GetLayerNum() noexcept;
		static const char* const* GetLayerNames() noexcept;

		static bool CheckValidationSupport() noexcept;

		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);
	};
}

#endif

#endif // GUARD