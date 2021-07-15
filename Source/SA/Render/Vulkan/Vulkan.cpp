// Copyright (c) 2021 Sapphire's Suite. All Rights Reserved.

#include <Render/Vulkan/Vulkan.hpp>

#include <Render/Vulkan/Debug/VkValidationLayers.hpp>

namespace Sa::Vk
{
	void Init()
	{
		SA_ASSERT(Default, SA/Render/Vulkan, ValidationLayers::CheckValidationSupport(), L"Validation Layers not supported!");
	}

	void UnInit()
	{
	}
}
