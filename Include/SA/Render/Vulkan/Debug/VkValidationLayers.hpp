// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_VALIDATION_LAYES_GUARD
#define SAPPHIRE_RENDER_VK_VALIDATION_LAYES_GUARD

#include <SA/Render/Vulkan/Debug/Debug.hpp>

#if SA_VK_VALIDATION_LAYERS

namespace Sa::Vk
{
	class ValidationLayers
	{
	public:
		~ValidationLayers() = delete;

		static VkDebugUtilsMessengerCreateInfoEXT GetDebugUtilsMessengerCreateInfo() noexcept;

		static uint32 GetLayerNum() noexcept;
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