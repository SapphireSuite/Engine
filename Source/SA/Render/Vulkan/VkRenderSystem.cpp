// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/VkRenderSystem.hpp>

#include <Core/Algorithms/SizeOf.hpp>

#include <Render/Vulkan/Debug/VkValidationLayers.hpp>

#include <Window/Base/AWindow.hpp>

namespace Sa::Vk
{
	std::vector<const char*> GetRequiredExtensions() noexcept
	{
		std::vector<const char*> extensions;

		// Query window API required extensions.
		AWindow::QueryRequiredExtensions(extensions);

#if SA_VK_VALIDATION_LAYERS

		extensions.push_back("VK_EXT_debug_utils");
#endif

		return extensions;
	}


	void RenderSystem::Create()
	{
		VkApplicationInfo appInfos;

		appInfos.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfos.pNext = nullptr;
		appInfos.pApplicationName = "Main Application";
		appInfos.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfos.pEngineName = "Sapphire Engine";
		appInfos.engineVersion = SA_ENGINE_VERSION;
		appInfos.apiVersion = VK_API_VERSION_1_0;


		std::vector<const char*> extensions = GetRequiredExtensions();


		VkInstanceCreateInfo instanceInfos;

		instanceInfos.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceInfos.pNext = nullptr;
		instanceInfos.flags = 0;
		instanceInfos.pApplicationInfo = &appInfos;

		instanceInfos.enabledLayerCount = 0;
		instanceInfos.ppEnabledLayerNames = nullptr;

		instanceInfos.enabledExtensionCount = static_cast<uint32>(SizeOf(extensions));
		instanceInfos.ppEnabledExtensionNames = extensions.data();

#if SA_VK_VALIDATION_LAYERS

		// Debug Messenger Info.
		const VkDebugUtilsMessengerCreateInfoEXT debugUtilscreateInfo = ValidationLayers::GetDebugUtilsMessengerCreateInfo();

		instanceInfos.pNext = &debugUtilscreateInfo;

		instanceInfos.enabledLayerCount = ValidationLayers::GetLayerNum();
		instanceInfos.ppEnabledLayerNames = ValidationLayers::GetLayerNames();
#endif

		SA_VK_ASSERT(vkCreateInstance(&instanceInfos, nullptr, &mHandle), L"Failed to create vulkan instance!");

#if SA_VK_VALIDATION_LAYERS

		auto createDebugFunc = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(mHandle, "vkCreateDebugUtilsMessengerEXT");
		SA_ASSERT(Nullptr, SA/Render/Vulkan, createDebugFunc, L"Extension PFN_vkCreateDebugUtilsMessengerEXT missing!");

		const VkResult res = createDebugFunc(mHandle, &debugUtilscreateInfo, nullptr, &mDebugMessenger);
		
		SA_ASSERT(Default, SA/Render/Vulkan, res == VK_SUCCESS, L"Failed to create vulkan debug messenger!");

		//SA_ASSERT(Default, SA/Render/Vulkan,
		//	createDebugFunc(mHandle, &debugUtilscreateInfo, nullptr, &mDebugMessenger) == VK_SUCCESS,
		//	L"Failed to create vulkan debug messenger!");
		
		//SA_VK_ASSERT(createDebugFunc(mHandle, &debugUtilscreateInfo, nullptr, &mDebugMessenger), L"Failed to create vulkan debug messenger!");

#endif
	}

	void RenderSystem::Destroy()
	{
#if SA_VK_VALIDATION_LAYERS

		auto destroyDebugFunc = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(mHandle, "vkDestroyDebugUtilsMessengerEXT");
		SA_ASSERT(Nullptr, SA/Render/Vulkan, destroyDebugFunc, L"Extension PFN_vkDestroyDebugUtilsMessengerEXT missing!");

		destroyDebugFunc(mHandle, mDebugMessenger, nullptr);

#endif


		vkDestroyInstance(mHandle, nullptr);
	}
}
