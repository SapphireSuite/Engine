// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/VkInstance.hpp>

#include <Render/Vulkan/Debug/Debug.hpp>

#include <Window/Base/AWindowInterface.hpp>

namespace SA::VK
{
	std::vector<const char*> GetRequiredExtensions(const AWindowInterface* _winIntf) noexcept
	{
		std::vector<const char*> extensions;

		// Query window API required extensions.
		if(_winIntf)
			_winIntf->QueryRequiredExtensions(extensions);

#if SA_VK_VALIDATION_LAYERS

		extensions.push_back("VK_EXT_debug_utils");
#endif

		return extensions;
	}


	void Instance::Create(const AWindowInterface* _winIntf)
	{
		VkApplicationInfo appInfos{};

		appInfos.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfos.pNext = nullptr;
		appInfos.pApplicationName = "Main Application";
		appInfos.applicationVersion = VK_MAKE_VERSION(1, 0, 0); // TODO:
		appInfos.pEngineName = "Sapphire Engine";
		appInfos.engineVersion = VK_MAKE_VERSION(1, 0, 0); // TODO:
		appInfos.apiVersion = VK_API_VERSION_1_0;


		const std::vector<const char*> extensions = GetRequiredExtensions(_winIntf);


		VkInstanceCreateInfo instanceInfos{};

		instanceInfos.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceInfos.pNext = nullptr;
		instanceInfos.flags = 0;
		instanceInfos.pApplicationInfo = &appInfos;

		instanceInfos.enabledLayerCount = 0;
		instanceInfos.ppEnabledLayerNames = nullptr;

		instanceInfos.enabledExtensionCount = extensions.size();
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
		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, createDebugFunc, L"Extension PFN_vkCreateDebugUtilsMessengerEXT missing!");

		SA_VK_ASSERT(createDebugFunc(mHandle, &debugUtilscreateInfo, nullptr, &mDebugMessenger), L"Failed to create vulkan debug messenger!");

#endif

		SA_LOG(L"Render Instance created.", Infos, SA/Engine/Render/Vulkan);
	}

	void Instance::Destroy()
	{
#if SA_VK_VALIDATION_LAYERS

		auto destroyDebugFunc = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(mHandle, "vkDestroyDebugUtilsMessengerEXT");
		SA_ASSERT(Nullptr, SA/Engine/Render/Vulkan, destroyDebugFunc, L"Extension PFN_vkDestroyDebugUtilsMessengerEXT missing!");

		destroyDebugFunc(mHandle, mDebugMessenger, nullptr);

#endif

		vkDestroyInstance(mHandle, nullptr);

		SA_LOG(L"Render Instance destroyed.", Infos, SA/Engine/Render/Vulkan);
	}


	Instance::operator VkInstance() const noexcept
	{
		return mHandle;
	}
}
