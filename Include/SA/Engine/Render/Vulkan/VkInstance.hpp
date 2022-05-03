// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_RENDER_VK_INSTANCE_GUARD
#define SAPPHIRE_ENGINE_RENDER_VK_INSTANCE_GUARD

#include <SA/Engine/Render/Vulkan/Debug/VkValidationLayers.hpp>

namespace Sa
{
	class AWindowInterface;
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
		void Create(const AWindowInterface* _winIntf = nullptr);
		void Destroy();

		operator VkInstance() const noexcept;
	};
}

#endif // GUARD
