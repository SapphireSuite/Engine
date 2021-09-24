// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_INSTANCE_GUARD
#define SAPPHIRE_RENDER_VK_INSTANCE_GUARD

#include <SA/Render/Vulkan/Debug/Debug.hpp>

#if SA_VULKAN

namespace Sa
{
	class AWindowSystem;
}

namespace Sa::Vk
{
	class Instance
	{
		VkInstance mHandle = VK_NULL_HANDLE;

#if SA_VK_VALIDATION_LAYERS

		VkDebugUtilsMessengerEXT mDebugMessenger = nullptr;

#endif

	public:
		void Create(const AWindowSystem& _winSys);
		void Destroy();

		operator VkInstance() const noexcept;
	};
}

#endif

#endif // GUARD
