// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_VK_QUEUE_REQUIREMENTS_GUARD
#define SAPPHIRE_ENGINE_VK_QUEUE_REQUIREMENTS_GUARD

#include <SA/Engine/Render/Vulkan/Device/Queue/VkQueueFamily.hpp>

namespace Sa::Vk
{
	struct QueueRequirements
	{
		Flags<QueueFamily> familyFlags = QueueFamily::Max;

		uint32_t graphicNum = 1;
		uint32_t computeNum = 1;
		uint32_t transferNum = 1;
		uint32_t presentNum = 1;
	};
}

#endif // GUARD
