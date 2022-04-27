// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <cstring> // std::strcmp

#include <Render/Vulkan/Debug/VkValidationLayers.hpp>

#if SA_VK_VALIDATION_LAYERS

namespace Sa::Vk
{
	static constexpr const char* validationLayers[] =
	{
		"VK_LAYER_KHRONOS_validation"
	};

	constexpr uint32_t validationLayersSize = sizeof(validationLayers) / sizeof(char*);

	VkDebugUtilsMessengerCreateInfoEXT ValidationLayers::GetDebugUtilsMessengerCreateInfo() noexcept
	{
		VkDebugUtilsMessengerCreateInfoEXT infos;

		infos.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		infos.pNext = nullptr;
		infos.flags = 0;

		infos.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
								VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
								VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

		infos.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
							VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
							VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

		infos.pfnUserCallback = ValidationLayers::DebugCallback;
		infos.pUserData = nullptr;

		return infos;
	}

	uint32_t ValidationLayers::GetLayerNum() noexcept
	{
		return validationLayersSize;
	}

	const char* const* ValidationLayers::GetLayerNames() noexcept
	{
		return validationLayers;
	}

	bool ValidationLayers::CheckValidationSupport() noexcept
	{
		// Query currently supported layers.
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());


		// Check each asked supported.
		for (uint32_t i = 0; i < validationLayersSize; ++i)
		{
			bool layerFound = false;

			for (uint32_t j = 0; j < availableLayers.size(); ++j)
			{
				// Layer found.
				if (std::strcmp(validationLayers[i], availableLayers[j].layerName) == 0)
				{
					layerFound = true;
					break;
				}
			}

			// Layer not found.
			if (!layerFound)
				return false;
		}

		return true;
	}

	VKAPI_ATTR VkBool32 VKAPI_CALL ValidationLayers::DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData)
	{
		(void)pUserData;

		std::wstring msgTypeStr;

		switch (messageType)
		{
			case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:
			{
				msgTypeStr = L"[General]";
				break;
			}
			case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
			{
				msgTypeStr = L"[Validation]";
				break;
			}
			case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT:
			{
				msgTypeStr = L"[Performance]";
				break;
			}
			default:
			{
				msgTypeStr = L"[Unknown]";
				break;
			}
		}

		switch (messageSeverity)
		{
			//case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
			//	break;
			case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
			{
				SA_LOG(pCallbackData->pMessage, Infos, SA/Render/Vulkan/VLayers, L"Vulkan Validation Layers " << msgTypeStr);
				break;
			}
			case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
			{
				SA_LOG(pCallbackData->pMessage, Warning, SA/Render/Vulkan/VLayers, L"Vulkan Validation Layers " << msgTypeStr);
				break;
			}
			case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
			{
				SA_LOG(pCallbackData->pMessage, Error, SA/Render/Vulkan/VLayers, L"Vulkan Validation Layers " << msgTypeStr);
				break;
			}
			default:
			{
				SA_LOG(pCallbackData->pMessage, Normal, SA/Render/Vulkan/VLayers, L"Vulkan Validation Layers " << msgTypeStr);
				break;
			}
		}

		return VK_FALSE;
	}
}

#endif
