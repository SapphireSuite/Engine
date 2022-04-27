// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_RENDER_VK_VALIDATION_LAYES_GUARD
#define SAPPHIRE_ENGINE_RENDER_VK_VALIDATION_LAYES_GUARD

#include <SA/Engine/Render/Vulkan/Debug/Debug.hpp>

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