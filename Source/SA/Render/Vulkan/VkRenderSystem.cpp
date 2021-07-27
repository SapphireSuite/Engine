// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/VkRenderSystem.hpp>

#include <Render/Vulkan/Debug/VkValidationLayers.hpp>

#if SA_VULKAN

namespace Sa::Vk
{
	void RenderSystem::Create()
	{
		SA_ASSERT(Default, SA/Render/Vulkan, ValidationLayers::CheckValidationSupport(), L"Validation Layers not supported!");
	}

	void RenderSystem::Destroy()
	{
	}
}

#endif
